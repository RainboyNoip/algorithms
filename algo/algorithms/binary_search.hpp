#pragma once
#include <algo/base.hpp>
#include <iterator>

namespace __MY_SELF__NAMESPACE__ {

// 第一个使用 Compare 不成立的 位置
template<typename Iter,
        typename Compare //= std::less< typename std::iterator_traits<Iter>::value_type >
    >
Iter bs(Iter first,Iter last,Compare&& __com){
    while ( first < last) {
        Iter m = first + (last - first)/2;
        if( __com(*m) )
            first = m+1;
        else
            last = m;
    }
    return last;
}


} //namespace __MY_SELF__NAMESPACE__
