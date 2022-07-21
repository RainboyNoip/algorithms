/**
 * l                     r
 * -----------------------
 *  [l,r)
 *  binary_search(l,r,compare)
 *  在一个单调的区间[l,r)的基础上,找到一个不符合__check的位置
 */
#pragma once
#include "../base.hpp"

namespace RALGO {

// 第一个使用 Compare 不成立的 位置
template<typename Iter,
        typename Compare = std::less< typename std::iterator_traits<Iter>::value_type >
    >
Iter binary_search(Iter first,Iter last,Compare&& __check
         = [](typename  std::iterator_traits<Iter>::value_type & v) {
            return v < 100;
        }
        )
{
    while ( first < last) {
        Iter m = first + (last - first)/2;
        if( __check(*m) )
            first = m+1;
        else
            last = m;
    }
    return last;
}


} //namespace RALGO
