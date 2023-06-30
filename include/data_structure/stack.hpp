//@desc 栈

#pragma once
#include "data_structure/dynamic_array.hpp"

template<typename T=int,std::size_t N=maxn>
using stack = dynamic_array<T, N>;



// 单调栈,TODO
template<typename T,std::size_t N = maxn>
struct monotonic_stack: public stack<T, maxn>{

};
