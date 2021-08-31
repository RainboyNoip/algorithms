#pragma once
#include <algo/base.hpp>
#include <iterator>

namespace __MY_SELF__NAMESPACE__ {

// 第一个使用 Compare 不成立的 位置
template<typename Iter,typename __VT,
        typename Compare = std::less< typename std::iterator_traits<Iter>::value_type >
    >
Iter bs(Iter first,Iter last,__VT&& value,Compare&& __com = Compare{}){
    while ( first < last) {
        //typename std::iterator_traits<Iter>::difference_type 
        Iter m = first + (last - first)/2;
        if( __com(*m,value) )
            first = m+1;
        else
            last = m;
    }
    return last;
}


} //namespace __MY_SELF__NAMESPACE__
