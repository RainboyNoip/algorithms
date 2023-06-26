//把环转成链,
//主要用于环型DP

#include "base.hpp"

//按点拆成环
//把点复制一遍
template<typename T,std::size_t N = maxn>
struct ring2chain_node{
    T a[maxn];
    int idx;

    ring2chain_node(): idx(0)
    {}

    inline
    void push(const T & v)
    {
        a[++idx] = v;
    }

    inline std::size_t size() const {
        return idx << 1;
    }

    T & operator[](std::size_t i) {
        if( i >= 1 && i <= idx)
            return a[i];
        else
            return a[i-idx];
    }

};
