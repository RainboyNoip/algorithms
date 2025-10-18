//@desc 栈

#pragma once
#include "data_structure/dynamic_array.hpp"

template<typename T=int,std::size_t N=maxn>
struct stack : public dynamic_array<T, N>
{
    using DA = dynamic_array<T, N>;

    using DA::push;
    using DA::empty;
    using DA::size;

    // template<typename... U>
    // using emplace = typename DA::emplace_back<U...>;

    // template<typename... U>
    using DA::emplace_back;

    inline T & top() {
        return DA::back();
    }

    template<typename... U>
    inline void emplace(U&&... args){
        emplace_back(std::forward<U>(args)...);
    }

    inline void pop() {
        DA::pop_back();
    }

};


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
