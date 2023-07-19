//@desc 栈

#pragma once
#include "data_structure/dynamic_array.hpp"

template<typename T=int,std::size_t N=maxn>
using stack = dynamic_array<T, N>;



// 单调栈,TODO
// 通常 T = {int idx,val;} 包含位置与值的信息
template<typename T,std::size_t N = maxn>
struct monotonic_stack: public stack<T, maxn>{

    // 添加元素,
    template<typename F>
    void push(T a,F && f);


    // 取顶部元素,符合f条件的全部删除
    template<typename F>
    void top(F&& f);

};
