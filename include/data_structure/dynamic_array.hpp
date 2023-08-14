//一个只能用于末尾增减的array,取代vector
// 使用方法
// 定义 dynamic_array<int,100> myarr;
// 末尾加入           myarr.push(a)
// 得到末尾的元素引用 myarr.back()
// 得到末尾的元素引用 myarr.top()
// 得到删除最后一个元素 myarr.pop()
// 使用下标操作  myarr[i],最小下标1
// 元素个数  myarr.size();
// 范围指针 begin() end()
// map 迭代
// myarr.map( [](int & v){ v += 100;})
// myarr.map( [](int idx,int & v){ if( idx % 2 ==0 ) v += 100 ;})
#pragma once
#include "base/macro.hpp"

template<typename T=int,std::size_t N=maxn>
struct dynamic_array {
    T a[maxn];
    int idx;

    using value_type = T;
    using iterator = T *;

    dynamic_array() :idx{0} {}

    inline void clear() { idx = 0; }

    void push(const T& v) {
        a[++idx] = v;
    }

    template<typename... U>
    inline void emplace_back(U&&... args){
        a[++idx] = {std::forward<U>(args)...};
    }

    bool empty() const {
        return size() == 0;
    }

    inline
    T & back() {
        return a[idx];
    }

    // inline
    // T & top() {
    //     return back();
    // }

    inline
    void pop_back() {
        --idx;
    }

    std::size_t size() const { return idx;}

    T * begin() {
        return &a[1];
    }

    T * end() {
        return &a[idx+1];
    }
    const T * begin() const {
        return &a[1];
    }

    const T * end() const {
        return &a[idx+1];
    }

    T & operator[](std::size_t id) {
        return a[id];
    }

    // wow ! like haskell Functor
    template<typename F>
    dynamic_array & map(F&& f) {
        for(int i = 1;i <= idx ;i++) {

            if constexpr (std::is_invocable_v<F,T> || std::is_invocable_v<F,T&>){
                f(a[i]);
            }
            else if constexpr(std::is_invocable_v<F,int,T>,std::is_invocable_v<F,int,T&>) {
                f(i,a[i]);
            }
#ifdef DEBUG
            else {
                throw std::invalid_argument("in dynamic_array map,map(Function),Function not invocable!");
            }
#endif
        }
        return *this;
    }

};


#ifdef  __FAST_OUT_
template<typename T>
fast_out & operator>>(fast_in & in,dynamic_array<T> & da) {
    // out.println(da.begin(), da.end());
    auto end = da.end();
    in >> *end;
    ++da.idx;
    return out;
}

template<typename T>
fast_out & operator<<(fast_out & out ,dynamic_array<T> & da) {
    out.println(da.begin(), da.end());
    return out;
}
#endif
