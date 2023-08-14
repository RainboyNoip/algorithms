// 提供一些碎片化的函数/代码
/*
-- upd_min(a,b) if a > b, a =b;
-- upd_max(a,b) if a < b, a=b;
-- is_in_range(a,l,r) if a in [l,r]

-- max_val(begin,end)
-- max_pos(begin,end)


*/
#pragma once
#include "base.hpp"
//计算一个数i 前面的第m个数是多少
//包括i本身
inline
int predecessor(int  i,const int & m) {
    return i-m+1;
}

//这个太复杂了,直接换成简单的函数
struct AdjacentNumberFinder {
    int m;

    AdjacentNumberFinder(int o)
        :m(o)
    {}

    //i前面第m个数是哪个
    inline
    int forward(int i) const{
        return i-m;
    }

    //i后面第m个数是哪个
    inline
    int backword(int i) const{
        return i+m;
    }

    friend
    int operator < (int i,const AdjacentNumberFinder & adj) {
        return adj.forward(i);
    }

    friend
    int operator > (int i,const AdjacentNumberFinder & adj) {
        return adj.backword(i);
    }
};


template<typename... T>
auto maximum(T&&... args) {
    return std::max({std::forward<T>(args)...});
}

template<typename T1,typename T2>
void upd_max(T1 & t,const T2& t2){
    if(t < t2)
        t = t2;
}

template<typename T1,typename T2>
void upd_min(T1 & t,const T2& t2){
    if(t > t2)
        t = t2;
}

//用最大的那个值更新T1
template<typename T1,typename T2,typename... T3>
void upd_max(T1 & t,const T2& t2, const T3 &... t3) {
    if(t < t2)
        t = t2;
    upd_max(t,t3...);
}

template<typename T>
inline bool is_in_range(T&& a,T && l, T&& r) {
    return a >= l && a <= r;
}

template<typename Iter,
    typename = std::void_t<decltype(*std::declval<Iter>(),++std::declval<Iter&>())> >
inline auto max_pos(Iter l,Iter r) {
    Iter pos = l;
    for( ; l != r; ++ l) {
        if( *pos < *l) pos = l;
    }
    return pos;
}


template<typename Iter,
    typename = std::void_t<decltype(*std::declval<Iter>(),++std::declval<Iter&>())> >
inline auto max_val(Iter l,Iter r) {
    return *max_pos(l,r);
}
