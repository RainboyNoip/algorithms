// -- 实现了rmq算法,基于double.hpp 倍增的基础代码
// 使用
// rmq myrmq;
// myrmq.set_orgin_array(a);
// myrmq.init();
// 查询区间[l,r]内的最值
// int _max = myrmq.query(l,r)
//

#pragma once
#include "algo/double.hpp"

//rmq算法,区间最值
//rmq与上的面的倍增的区别,
template<std::size_t N = maxn>
struct rmq : public multi_double<rmq,N>{

    using multi_double<rmq,N>::f;
    using multi_double<rmq,N>::init;

    int * a = nullptr; //原数组

    //设定原数组
    template<std::size_t sz>
    void set_orgin_array(int (&arr)[sz] )
    {
        a = arr;
    }

    inline int get0(int i) {
#ifdef DEBUG
        if (a == nullptr)
            throw  std::invalid_argument("not set origin  array, pls rum set_orgin_array(a[])");
#endif
        return a[i+1];
    }

    //a,b两个区间的信息,如何合并的
    int merge_impl(int a,int b){
        return a> b? a : b;
    }

    //查询
    int query(int l,int r) const {
        int j = floor_log(r-l+1);
        return std::max(f[l-1][j],f[pre_pos(r,j)][j]);
    }

};
