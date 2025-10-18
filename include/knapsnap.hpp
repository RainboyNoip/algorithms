#pragma once

//01背包的实现
//
#pragma once

#include <cstring>
#include <array>
#include <iostream>

//使用crtp
/// 检查MyClass是否有foo函数
#ifdef __cpp_lib_concepts

template<typename T>
concept has_init_member_function_v = requires(T t) {
    t.init();
};

#else

// 使用 SFINAE
template<typename T>
struct has_init_member_function {
    template<typename U, void (U::*)()> struct sfinae;
    template<typename U> static char test(sfinae<U, &U::init>*);
    template<typename U> static int test(...);
    static const bool value = sizeof(test<T>(0)) == sizeof(char);
};

template<typename T>
constexpr bool has_init_member_function_v = has_init_member_function<T>::value;

#endif

template<size_t N,template<std::size_t> class Driv>
struct knapsnap_base {

    using DrivType = Driv<N>;
    //存dp的值 f[i] = max{f[i],f[i-v]+w}
    int f[N+5] = {0};
    

    inline void _init() { //这个名字不会和子类的init重复
        if constexpr ( has_init_member_function_v<DrivType>)
            static_cast<DrivType*>(this) -> init();
        else
            memset(f,0,sizeof(f));
    }

    inline void push_item(int w,int v) {
        // static_cast<Driv*>(this) -> push_item_impl(w,v);
        for( int i = N;i >= w; --i) {
            static_cast<DrivType*>(this) -> update_impl(i,w,v);
        }
    }

    knapsnap_base() {
        _init();
    }

    //在容量为v时的最大价值
    inline int& val(int v) { return f[v];}
};

//普通01背包
template<std::size_t N>
struct knapsnap_01 : public knapsnap_base<N,knapsnap_01> {
    using knapsnap_base<N,knapsnap_01>::f;
    void update_impl(int i,int w,int v) {
        if( int t = f[i-w] + v; t > f[i])
            f[i] = t;
    }
};

//01背包恰好装满
//这里默认的情况是 f[0] 表示不可能装满
template<std::size_t N>
struct knapsnap_01_full : public knapsnap_base<N,knapsnap_01> {
    using knapsnap_base<N,knapsnap_01>::f;

    void update_impl(int i,int w,int v) {
        if( int t = f[i-w]; t > 0 && t+v > f[i])
            f[i] = t+v;
    }
};

// 完全背包
template<std::size_t N>
struct knapsnap_full : public knapsnap_01<N> {
    using knapsnap_01<N>::update_impl;

    void push_item(int w,int v) {
        for(int i = w ;i<= N ;i++ )
            update_impl(i,w,v);
    }
};

//分组背包
template<std::size_t N>
struct knapsnap_group: public knapsnap_01<N> {
    // using knapsnap_base<N,knapsnap_01>::f;
    using knapsnap_01<N>::update_impl;

    struct item { int w,v; };

    struct groupType {
        std::array<item,N> g;
        int idx = 0;
        inline void clear() { idx = 0;}
        int size() const { return idx;}
        void push(int w,int v) {
            g[idx++] = {w,v};
        }
    };

    //更新一组物品
    void push_group(const groupType & group) {
        for( int i = N ;i >= 0 ;--i) {
            for(int j = 0 ;j < group.size() ; ++j) {
                if( group.g[j].w < i) continue;
                update_impl(i,group.g[j].w,group.g[j].v);
            }
        }
    }
};


/*

//TODO change ex for 恰好
//默认
//f[i] = 0 没有安装满,也可以是不成立
//f[i] > 0 成立
template<std::size_t size>
struct knapsnap_01_ex_full : public knapsnap_01<size> {
    using knapsnap_01<size>::f; //使用模板基类的成员,需要指定模板参数
    inline void update(int i,int w,int v) override {
        if( int t = f[i-w]; t > 0)
            f[i] = t + v;
    }
};



//多重背包
//
//混合三种背包

//分组背包
template<std::size_t N>
struct knapsnap_group : public knapsnap_base<N> {
    using knapsnap_base<N>::f;

    //在分组背包中,物品不是一个,而是一组
    void push_group(int w,int v,int len) {

    }

private:

};

*/
