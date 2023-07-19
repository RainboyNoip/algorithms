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

    inline
    T & back() {
        return a[idx];
    }

    inline
    T & top() {
        return back();
    }

    inline
    void pop() {
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
};


#ifdef  __FAST_OUT_
template<typename T>
fast_out & operator<<(fast_out & out ,dynamic_array<T> & da) {
    out.println(da.begin(), da.end());
    return out;
}
#endif
