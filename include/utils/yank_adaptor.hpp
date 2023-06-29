/**
 * 灵感来自c++20 rangeAdatpor, 作用: 从左边抽取数据存入右边
 *
 * 使用方法
 *
 * 1. 传递一个lambda 给YankAdaptor 类创建一个
 *
 */

#include "base.hpp"

// 创建一个YankActionAdaptor 
// auto read = YankAdaptor = [](int n ,auto & left, auto& right) { 
//     for(int i = 1;i<=n;i++){
//          int u; left >> u;
//          right.add(u);
//     }
// }
// fastIO >> read(5) >> container

template<typename _leftContainer,typename _Callable,
typename... _CallableArgs >
struct YankActionAdaptor {
    _leftContainer  _M_leftContainer;
    _Callable _M_callable;
    std::tuple<_CallableArgs...> m_tup;

    YankActionAdaptor(_leftContainer&& lc,_Callable cal,_CallableArgs&&... cargs)
        :_M_leftContainer(std::forward<_leftContainer>(lc)),
        _M_callable(cal),
        m_tup(std::make_tuple(std::forward<_CallableArgs>(cargs)...))
    {}

    YankActionAdaptor(_leftContainer&& lc,_Callable cal,std::tuple<_CallableArgs...>&& tup)
        :_M_leftContainer(std::forward<_leftContainer>(lc)),
        _M_callable(cal),
        m_tup(std::move(tup))
    {}


    // template<typename... T>
    // YankActionAdaptor(std::tuple<T...>&& tup)
    // :m_tup(std::move(tup)
    // {}

    template<typename leftContainer>
    auto accept_leftContainer(leftContainer & lc) {
        return YankActionAdaptor
            <leftContainer&,_Callable,_CallableArgs...>
            (lc,_M_callable,std::move(m_tup));
    }

    template<typename... T>
    auto operator()(T&& ...args) {
       return YankActionAdaptor(
               std::move(_M_leftContainer), // ? 一个 reference 如何std::move ?
               std::move(_M_callable),
               std::forward<T>(args)...
               );
    }
    
    //执行
    template< typename _RightContainer >
    auto operator>>(_RightContainer & rc ) {
        // 测试输出
        return [&]<std::size_t... I>(std::index_sequence<I...>){
            return std::invoke(
                    _M_callable,
                    std::get<I>(m_tup)...,
                    _M_leftContainer,
                    rc);
        }(std::make_index_sequence<std::tuple_size_v<decltype(m_tup)> >{});

        /*
        return [&]<auto... I>(auto __){
            return std::invoke(
                    _M_callable,
                    std::get<I>(m_tup)...,
                    _M_leftContainer,
                    rc);
        }(std::make_index_sequence<std::tuple_size_v<decltype(m_tup)> >{});
        */
    }

};

template<typename _Callable>
struct YankAdaptor {

    _Callable _M_callable;

    YankAdaptor(const _Callable & _callable)
        :_M_callable(_callable)
    { }

    YankAdaptor(_Callable && _callable)
        : _M_callable( std::move( _callable))
    {}

    //创建一个AdaptorAction
    template<typename... Args>
    requires (sizeof... (Args) >=1 )
    constexpr auto
    operator()(Args&& ... args) const {
        return YankActionAdaptor(0,_M_callable,std::forward<Args>(args)...);
    }
};

