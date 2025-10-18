//前缀和
#include "base/macro.hpp"

template<typename T=long long,std::size_t N=maxn>
struct pre_sum {
    T a[maxn] = {0};
    int tot;
    
    pre_sum() : tot(0) {
        a[0] = 0;
    }

    //添加一个元素
    inline void push(T v) {
        a[tot+1] = a[tot] + v;
        ++tot;
    }

    template<typename U,std::size_t L>
    pre_sum(U (&arr)[L], int len)
    {
        init( arr,len);
    }

    template<typename U,std::size_t L>
    void init(U (&arr)[L], int len)
    {
        a[0] = 0;
        for(int i = 1;i <= len ;++i ) // i: 1->len
            push(arr[i]);
    }

    //求区间和
    T sum(int l,int r) {
        if(l>r) return 0;
        if( r > tot) r = tot; // 超过范围的r,就是最后一个位置
        return a[r] - a[l-1];
    }
};

