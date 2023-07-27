#ifndef  __ALGORITHM__lambda__
#define  __ALGORITHM__lambda__
#pragma once

#include "base/macro.hpp"

namespace lambda {

namespace  detail {

// 得到操作[]的索引
// 对第一个参数 进行[t2] 索引
struct  subscript {
    template<typename T1 ,typename T2>
    decltype(auto) operator()( T1&& t1, T2 && t2) const {
        return std::forward<T1>(t1)[ std::forward<T2>(t2)];
    }
};

//间接调用 std::get
template<std::size_t I>
struct get{
    template<typename T>
    decltype(auto) operator()(T&& t) const {
        return std::get<I>(std::forward<T>(t));
    }
};

} // end namespace detail

template<std::size_t I>
struct lambda2_arg {

    //从一堆参数中挑出第i个
    template<typename... Args>
    decltype(auto) operator()(Args&&... args) const noexcept
    {
        return  std::get<I-1>(std::tuple<Args&&...>(std::forward<Args>(args)...));
    }

    /*
    产生一个类似于,下面的函数
    
    [](Args... args){
        auto x = _1(args...); //得到第一个参数
        auto y = 0; //记录下y是第二个参数
        auto sub = subscript;
        return subscript(x,y);//最后的调用
    }
    */
    template<typename T>
    auto operator[](T&& t) const
    {
        return std::bind(detail::subscript(),*this,std::forward<T>(t));
    }

};


#if defined(__cpp_inline_variables) && __cpp_inline_variables >= 201606L
# define __LAMBDA2_INLINE_VAR inline
#else
# define __LAMBDA2_INLINE_VAR
#endif

__LAMBDA2_INLINE_VAR constexpr lambda2_arg<1> _1{};
__LAMBDA2_INLINE_VAR constexpr lambda2_arg<2> _2{};
__LAMBDA2_INLINE_VAR constexpr lambda2_arg<3> _3{};
__LAMBDA2_INLINE_VAR constexpr lambda2_arg<4> _4{};
__LAMBDA2_INLINE_VAR constexpr lambda2_arg<5> _5{};
__LAMBDA2_INLINE_VAR constexpr lambda2_arg<6> _6{};
__LAMBDA2_INLINE_VAR constexpr lambda2_arg<7> _7{};
__LAMBDA2_INLINE_VAR constexpr lambda2_arg<8> _8{};
__LAMBDA2_INLINE_VAR constexpr lambda2_arg<9> _9{};


} // end namespace lambda

namespace std
{

template<size_t I> 
struct is_placeholder< lambda::lambda2_arg<I> >: integral_constant<int, I>{};

} // namespace std


#endif
