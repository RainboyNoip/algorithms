//一个只能用于末尾增减的array
#pragma once
#include "base.hpp"

template<typename T=int,std::size_t N=maxn>
struct dynamic_array {
    T a[maxn];
    int idx;

    using value_type = T;
    using iterator = T *;

    dynamic_array() :idx{0} {}

    inline void clear() { idx = 0; }

    void push(const T& v) {
        a[idx++] = v;
    }

    inline
    T & back() {
        return a[idx-1];
    }

    inline
    T & top() {
        return back();
    }

    inline
    void pop() {
        idx--;
    }

    std::size_t size() const { return idx;}

    T * begin() {
        return &a[0];
    }

    T * end() {
        return &a[idx];
    }
    const T * begin() const {
        return &a[0];
    }

    const T * end() const {
        return &a[idx];
    }


    T & operator[](std::size_t id) {
        return a[id];
    }
};


template<typename T>
fast_out & operator<<(fast_out & out ,dynamic_array<T> & da) {
    out.println(da.begin(), da.end());
    return out;
}
