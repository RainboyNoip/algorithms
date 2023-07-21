// https://zh.wikipedia.org/wiki/%E9%93%BE%E5%BC%8F%E5%89%8D%E5%90%91%E6%98%9F
//[链式前向星及其简单应用 | Malash's Blog](https://malash.me/200910/linked-forward-star/)
/**
 * 存树与图的基础数据结构
 * 具体使用见 examples/linkList.cpp
 * 使用:
 *   1. 定义
 *   - graph gh; 无向有边权
 *   - graph_nw gh; 无有无边权
 *   - digraph gh;  无向有边权
 *   - digraph_nw gh;   有向无边权
 *
 *   2. 添加边
 *      gh.add(u,v) 无边权添加边
 *      gh.add(u,v,w) 有边权添加边
 *
 *   3. 遍历以u为起点边的所有边
 * for(int i = e.head(u);~i;i = e.next(i)){
 *    int v = e[i].v, w = e[i].w;
 * }
 * for( auto &[v,w] : e.start_from_head(u) ) {
 *    
 * }
 *   
 *
 */

#pragma once

#include "base/macro.hpp"
#include "data_structure/adjacencyList.hpp" // 基于adjacencyList

//存一条边
struct edge {
    int v,w;
    //当做一个int时,记录的就是当前点
    operator int() { return v; }
};

namespace std {
    template <> struct tuple_size<edge> : std::integral_constant<size_t, 2> { };
    template <> struct tuple_element<0,edge> { using type = int; };
    template <> struct tuple_element<1,edge> { using type = int; };

    //解引用 auto [v,w] = e;
    template <std::size_t I>
    auto get(edge const& x) { static_assert(I<=1,"I must <= 1");}

    template <>
    auto get<0>(edge const& x) { return x.v; }

    template <>
    auto get<1>(edge const& x) { return x.w; }
}

//没有边权的边
using edge_no_w = int;

template<typename T>
struct is_edge : public std::is_same<T,edge> {};

template<typename T>
struct is_edge_no_w : public std::is_same<T, edge_no_w>{};


//图的类型
enum class GraphType {
    direct_graph,
    undirect_graph
};

constexpr auto direct_graph =GraphType::direct_graph; //有向图
constexpr auto undirect_graph =GraphType::undirect_graph; //无向图

/**
* 说明:边的编号从0的开始
*/
template<GraphType Type,typename Edge,std::size_t V_CNT=maxn,std::size_t E_CNT=maxe>
struct linkList :public adjacencyList<Edge,V_CNT,E_CNT>
{
    using ADJ =  adjacencyList<Edge, V_CNT, E_CNT>;
    using ADJ::clear;
    // using ADJ::push;
    using ADJ::size; //得到边的数量
    using ADJ::head; //返回以u为起点的第一条边的编号
    using ADJ::next; //返回下一条同起点边的编号
    using ADJ::start_from_head;
    using ADJ::for_each;
    
    static constexpr bool is_direct = Type == GraphType::direct_graph;
    static constexpr bool is_undirect = Type == GraphType::undirect_graph;

    linkList() : ADJ() {}

    //最后一条边的编号
    int last_edge_idx() const {return size()-1;}

    //返回第i条边的编号
    Edge& operator[](int i){ return ADJ::mem[i]; }

    //注: 只能用于无边权
    void add(int u,int v) {
        if constexpr ( not is_edge_no_w<Edge>::value)
            throw std::invalid_argument("add(u,v) must apply to edge without weight !");
        ADJ::push(u,v);
        if constexpr ( is_undirect)
            ADJ::push(v,u);
    }

    //注: 只能用于有边权
    void add(int u,int v,int w) {
        if constexpr ( not is_edge<Edge>::value)
            throw std::invalid_argument("add(u,v,w) must apply to edge with weight!");
        ADJ::emplace_back(u,v,w);
        if constexpr ( is_undirect)
            ADJ::emplace_back(v,u,w);
    }
};



// fast_io 读取数据
#ifdef  __FAST_OUT_
template<GraphType Type,typename Edge,std::size_t V_CNT, std::size_t E_CNT>
void operator>>(fast_in & in,linkList<Type,Edge, V_CNT, E_CNT> & e) {
    int u,v,w=0;
    if constexpr (is_edge<Edge>::value) //有向图
    {
        in.read(u,v,w);
        e.add(u,v,w);
    }
    else if constexpr (is_edge_no_w<Edge>::value)
    {
        in.read(u,v);
        e.add(u,v);
    }
}

fast_out & operator<<(fast_out & out ,const edge & e) {
    out.println(e.v,e.w);
    return out;
}
#endif


//无向图,有边权
using graph = linkList<undirect_graph,edge,maxn,maxe>;

//树
using Tree  = graph;

//无向图,无边权
using graph_nw = linkList<undirect_graph,edge_no_w,maxn,maxe>;

//有向图,有边权
using dirgraph = linkList<direct_graph,edge,maxn,maxe>;

//有向图,无边权
using dirgraph_nw = linkList<direct_graph,edge_no_w,maxn,maxe>;
