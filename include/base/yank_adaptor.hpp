/**
 * 灵感来自c++20 rangeAdatpor, 作用: 
 *  
 *  1. 从左边抽取数据存入右边
 *      int a[10];
 *      in >> YankArray(5) >> a; # 读取5个数,存入 a[1] ~ a[5]
 *  2. 从左边抽取数据输出
 *      a >> YankArray(5) >> out;
 *      输出a[1]~a[5]
 *  3. 通过修改默认的 in >> 或 out << 的operator 来实现对结构的写入,输出
 *        具体看 example/base/yank_adaptor.cpp
 *  4. 只要是两个容器之间的数组传递,都可以使用
 *      
 *
 * 使用方法
 *
 * 1. 传递一个lambda 给YankAdaptor 类创建一个 YankAdaptor 对象
 * 2. YankAdaptor对象可以通过operator() 接收 lambda 需要执行的参数,
 *    并返回YankActionAdaptor action1
 * 3. Container >> action1 右容器创建
 * 4. 需要各个容器 创建 操作 >>
 *
 * template<>
 * void operator>>(type A1 & a, void_yank_action)
 *
 */

// 创建一个YankActionAdaptor 
// auto read = YankAdaptor = [](int n ,auto & left, auto& right) { 
//     for(int i = 1;i<=n;i++){
//          int u; left >> u;
//          right.add(u);
//     }
// }
// fastIO >> read(5) >> container
#pragma once
#include "base.hpp"

template<typename _leftContainer,typename _Callable,typename... _CallableArgs >
struct YankActionAdaptor;

// 功能
// 1. 存 callback, callback args... 容器
// 2. 接收一个左边的容器,产生YankActionAdaptor
template<typename _Callable,typename... _CallableArgs >
struct YankDataContainer {

    using tuple_type = std::tuple<_CallableArgs...>;

    _Callable _M_callable;
    std::tuple<_CallableArgs...> m_tup;

    YankDataContainer(_Callable cal,_CallableArgs&&... cargs)
        : _M_callable(cal),
        // m_tup(std::make_tuple(std::forward<_CallableArgs>(cargs)...))
        m_tup(std::forward<_CallableArgs>(cargs)...)
    {}

    YankDataContainer(_Callable cal,std::tuple<_CallableArgs...>&& tup)
        : _M_callable(cal),
        m_tup(std::move(tup))
    {}

    //接收左容器
    template<typename leftContainer>
    auto accept_leftContainer(leftContainer & lc) {
        return YankActionAdaptor
            <leftContainer&,_Callable,_CallableArgs...>
            (lc,std::move(*this));
    }
};

// 包含一个左容器
// 一个 YankDataContainer
// 只需要一个 >> 一个右容器就会执行
template<typename _leftContainer,typename _Callable,typename... _CallableArgs >
struct YankActionAdaptor {
    _leftContainer  _M_leftContainer;
    YankDataContainer<_Callable,_CallableArgs...> _M_calldata;
    
    using DataType = YankDataContainer<_Callable,_CallableArgs...>;

    YankActionAdaptor(_leftContainer&& lc,DataType&& _callable)
        :_M_leftContainer(std::forward<_leftContainer>(lc)),
        _M_calldata(std::move(_callable))
    {}

    //将数据存入到 _RightContainer
    //真正的执行 lambda
    template< typename _RightContainer >
    auto operator>>(_RightContainer & rc ) {
        // 测试输出
        return [&]<std::size_t... I>(std::index_sequence<I...>){
            return std::invoke(
                    _M_calldata._M_callable,
                    std::get<I>(_M_calldata.m_tup)...,
                    _M_leftContainer,
                    rc);
        }(std::make_index_sequence<std::tuple_size_v<typename DataType::tuple_type> >{});
    }
};

//user CTD
template<typename _leftContainer,typename _Callable,typename... _CallableArgs >
YankActionAdaptor(_leftContainer&&,YankDataContainer<_Callable,_CallableArgs...>)
    ->YankActionAdaptor<_leftContainer, _Callable, _CallableArgs...>;


//两个功能
//1. 先接受一个 lambda 构造参数,成功YankAdaptor对象
//2. YankAdaptor对象,通过operator(args...) 接收lambda 的参数,生成YankDataContainer
template<typename _Callable>
struct YankAdaptor {

    _Callable _M_callable;

    YankAdaptor(const _Callable & _callable)
        :_M_callable(_callable)
    { }

    YankAdaptor(_Callable && _callable)
        : _M_callable( std::move( _callable))
    {}

    //创建一个void AdaptorAction,不包包含容器
    template<typename... Args>
    requires (sizeof... (Args) >=1 )
    constexpr auto
    operator()(Args&& ... args) const {
        // return YankDataContainer<_Callable,Args...>(_M_callable,std::forward<Args>(args)...);
        return YankDataContainer<_Callable,
               std::remove_cv_t<Args>...
               >(_M_callable,std::forward<Args>(args)...);
    }
};

//类型萃取

template<typename T>
struct is_YankDataContainer: public std::false_type {};

template<typename T2,typename... Args>
struct is_YankDataContainer<YankDataContainer<T2,Args... >> : public std::true_type {};


template<typename T>
struct is_YankActionAdaptor: public std::false_type {};

template<typename LC,typename _Callable,typename... _CallableArgs>
struct is_YankActionAdaptor
<YankActionAdaptor<LC,_Callable,_CallableArgs...>>
: public std::true_type {};


// 接收一个左边的容器,产生YankActionAdaptor
template<typename ContainerLeft,typename T2>
requires is_YankDataContainer<T2>::value
auto operator>>(ContainerLeft & lc,T2&& _yankData)
{
    return YankActionAdaptor(lc,std::move(_yankData));
}

template <typename T>
concept OneDimensionalArray = std::rank_v<T> == 1 && std::extent_v<T> > 0;

template <typename T>
concept TwoDimensionalArray = std::rank_v<T> == 2 && std::extent_v<T> > 0;

//可以被YankArray
template <typename lc,typename rc>
concept CanYankLikeArray = requires(lc & l,rc & r)
{
    {l >> r};
};

/*

//向一维数组写
auto YankArray = YankAdaptor([]<typename T1,typename T2>(int count,T1 & lc,T2 & rc){ 
    if constexpr ( OneDimensionalArray<T2>) {
        for(int i=1;i<=count;++i){
            lc >> rc[i];
        }
    }
    else if constexpr ( OneDimensionalArray<T1> && std::is_same_v<T2, fast_out>)
    {
        for(int i=1;i<=count;++i){
            rc.print_sp(lc[i]);
        }
        rc.println(lc[count]);
    }
    else if constexpr ( CanYankLikeArray<T1,T2>) {
        for(int i=1;i<=count;++i)
            lc >> rc;
    }
    else assert(false);
    // else static_assert(false,"errors");
});

auto Yank2DArray = YankAdaptor([]<typename T1, typename T2>(int n,int m,T1 & lc,T2 & rc){ 
    if constexpr ( TwoDimensionalArray<T2>) {
        for(int i=1;i<=n;++i){
            for(int j=1;j<=m;++j){
                lc >> rc[i][j];
            }
        }
    }
    else if constexpr ( TwoDimensionalArray<T1> && std::is_same_v<T2, fast_out>)
    {
        for(int i=1;i<=n;++i){
            for(int j=1;j<m;++j){
                // lc[i][j] >> rc;
                rc.print_sp(lc[i][j]);
            }
            rc.println(lc[i][m]);
        }
    }
});
*/


// 接收一个左边的容器,产生YankActionAdaptor
template<typename T2>
requires is_YankDataContainer<T2>::value
auto operator>>(fast_in & lc,T2&& _yankData)
{
    return YankActionAdaptor(lc,std::move(_yankData));
}



//一维数组的输出

// template<typename T2>
// requires is_YankActionAdaptor<T2>::value
// auto operator>>(T2&& _yankAction,fast_out& out)
// {
//     return YankActionAdaptor(lc,std::move(_yankData));
// }

//可以创建自己的default_yank_action 来实现不同的效果 

//默认的行为
template<typename LC,typename RC>
void default_yank_action(int i,LC & lc ,RC & rc)
{
    lc >> rc;
}

template<typename LC,typename RC>
requires OneDimensionalArray<RC>
void default_yank_action(int i,LC & lc ,RC & rc)
{
    lc >> rc[i];
}

//lc是一个一维数组,而RC是fast_out
template<typename LC,typename RC>
requires OneDimensionalArray<LC> && std::is_same_v<RC, fast_out>
void default_yank_action(int i,LC & lc ,RC & rc)
{
    rc << lc[i]; //输出这个元素
}



// YankArray 一维的读取数据
// lc >> YankArray(5) >> rc; 只会默认的执行 5次
// lc >> YankArray(5)([](int i,auto & lc ,auto &rc){
//     lc >> rc.w; //
//     Do other
//
// }) >> rc;
struct YankArray {
    int cnt;

    YankArray(int n) // 初始化循环次数
        :cnt(n)
    {}

    //生成一个YankDataContainer
    template<typename Lambda>
    auto operator()(Lambda&& act) const {
        return YankDataContainer(
                [count=cnt,f=std::move(act)]
                    (auto &lc,auto &rc)
                {
                    for(int i =1;i<=count;++i) {
                        if constexpr ( OneDimensionalArray<decltype(rc)>)
                            f(lc,rc[i]);
                        // if constexpr ( std::is_invocable_v<decltype(f), int ,decltype(lc),decltype(rc)>)
                        //     f(i,lc,rc);
                        // else
                        //     f(lc,rc);
                    }
                }
        );
    }
};


//不传递lambda的行为,默认的行为
template<typename LC>
auto operator>>(LC & lc ,const YankArray & ya)
{
    auto _yankData = YankDataContainer([count=ya.cnt](auto & lc,auto & rc){
                for(int i=1;i<=count;++i)
                    default_yank_action(i,lc,rc);
            });
    return _yankData.accept_leftContainer(lc);
}
