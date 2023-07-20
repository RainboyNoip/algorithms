/*---
{
"info":"链式前向星,存图",
"word":"linkList",
"expand":"linkList<MaxN> e;",
"user_data":"ralgo"
}
---*/
// https://zh.wikipedia.org/wiki/%E9%93%BE%E5%BC%8F%E5%89%8D%E5%90%91%E6%98%9F
//[链式前向星及其简单应用 | Malash's Blog](https://malash.me/200910/linked-forward-star/)
/**
 * 存树与图的基础数据结构
 * 具体使用见 examples/linkList.cpp
 * 使用:
 *   1. 定义
 * linkList e1;         //定义一个默认有 10^6个点,10^6个边的 存储结构
 * linkList<100> e2;    //定义一个有 100个点,10^6个边的 存储结构
 * linkList<100,100> e3;//定义一个有 100个点,100 个边的 存储结构
 *
 *   2. 添加边
 * e.add(u,v)
 * e.add(u,v,w)
 * e.add2(u,v)
 * e.add2(u,v,w)
 *
 *   3. 遍历以u为起点边的所有边
 * for(int i = e.head(u);~i;i = e[i].next){
 *    int v = e[i].v, w = e[i].w;
 * }
 * for( auto &[v,w] : e.edges_start_for(u) ) {
 *    
 * }
 *   
 *
 */

#pragma once

#include <cassert>
#include "base.hpp"


//存一条边
struct edge {
    int v,w,next;

    //当做一个int时,记录的就是当前点
    operator int() { return v; }
};

//没有边权的边
struct edge_no_w {
    int v,next;
    operator int() { return v; }
};


template<typename T>
struct is_edge : public std::false_type{};

template<>
struct is_edge<edge> : public std::true_type{};


template<typename T>
struct is_edge_no_w : public std::false_type{};

template<>
struct is_edge_no_w<edge_no_w> : public std::true_type{};


fast_out & operator<<(fast_out & out ,const edge & e) {
    out.println(e.v,e.w);
    return out;
}

fast_out & operator<<(fast_out & out ,const edge_no_w & e) {
    out.println(e.v);
    return out;
}


void make_edge(edge & e,int v,int w,int next) {
    e.v = v,e.w = w,e.next = next;
}

void make_edge(edge_no_w & e,int v,int w,int next) {
    e.v = v,e.next = next;
}


//图的类型

struct direct_graph {}; //有向图
struct undirect_graph {}; // 无向图


/**
* 说明:边的编号从0的开始
*/
template<typename GraphType,typename Edge = edge,std::size_t V_CNT=maxn,std::size_t E_CNT=maxe>
class linkList {

private:

    using type = GraphType;
    
    Edge e[E_CNT];
    int h[V_CNT],edge_cnt=0;

public:
    
    linkList(){	//构造函数
        edge_cnt=0;
        memset(h,-1,sizeof(h));
    }

    //遍历点u 周围点
    template<typename U>
    void for_each(int u,U func){
        for(int i = h[u] ; i !=-1;i = e[i].next)
            func(e[i].u,e[i].v,e[i].w); //u v w
    }

    inline void emplace_back(int u,int v,int w = 0) {
        make_edge(e[edge_cnt], v, w, h[u]);
        h[u] = edge_cnt++;
    }

    inline void add(int u,int v,int w=0){
        emplace_back(u,v,w);
        if constexpr (std::is_same<GraphType, undirect_graph>::value)
            emplace_back(v,u,w);
    }

    //最后一条边的编号
    int last_edge_idx() const {return edge_cnt-1;}
    int get_edge_cnt() const { return edge_cnt;}

    // TODO 有向图
    // void add2(int u,int v,int w=0){
    //     add(u,v,w);
    //     add(v,u,w);
    // }

    //返回以u为起点的第一条边的编号
    int head(int u) const{ return h[u]; }

    int next(int idx) const { return e[idx].next; }

    //返回第i条边的编号
    Edge& operator[](int i){ return e[i]; }

    //for (auto& e : c)  --> for(auto i = c.begin() ; i!= c.end() ; i++)
    /*(since C++20)
     *{
     *    init-statement
     *        auto && __range = range-expression ; auto __begin = begin-expr ; auto __end = end-expr ;
     *    for ( ; __begin != __end; ++__begin)
     *    {
     *        range-declaration = *__begin;
     *        loop-statement
     *    }
     *}
     * 1. 解析引用
     * 2. range.begin()
     * 3. range.end()
     * 4. ++操作符号
     */

    struct edgePoint {
        linkList * self; //指向linkList的指针
        int idx;

        edgePoint(linkList * l,int edge_idx) : self{l},idx{edge_idx} 
        {}

        bool operator!=(int a){ return idx != a;};

        edgePoint& operator++() {
            if( idx != -1) idx = self->e[idx].next;
            return *this;
        }

        Edge& operator*(){
            return self->e[idx];
        }
    };
    struct EdgeIterator {
        linkList * self; //指向linkList的指针
        int u; //哪个点周围的点
        edgePoint begin() { return {self,self->h[u]}; }
        int end(){ return -1;}
    };

    EdgeIterator edges_start_for(int u){
        return {this,u};
    }


    // TODO 遍历所有的点
    // 只能假定认为点是连续的,且从1开始?
    // auto begin() 
};


template<typename T>
struct linklist_traits {};

template<typename GraphType,typename Edge,std::size_t V_CNT, std::size_t E_CNT>
struct linklist_traits<linkList<GraphType,Edge,V_CNT,E_CNT>> {
    using type = GraphType;

    static constexpr bool is_direct = std::is_same_v<GraphType, direct_graph>;
    static constexpr bool is_undirect = std::is_same_v<GraphType, undirect_graph>;

};


// fast_io 读取数据

template<typename GraphType,typename Edge,std::size_t V_CNT, std::size_t E_CNT>
void operator>>(fast_in & in,linkList<GraphType,Edge, V_CNT, E_CNT> & e) {
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

//无向图,有边权
using graph = linkList<undirect_graph,edge,maxn,maxe>;

//无向图,无边权
using graph_nw = linkList<undirect_graph,edge_no_w,maxn,maxe>;

//有向图,有边权
using dirgraph = linkList<direct_graph,edge,maxn,maxe>;

//有向图,无边权
using dirgraph_nw = linkList<direct_graph,edge_no_w,maxn,maxe>;

//如何 使 struct binding 支持自己的类型
//https://stackoverflow.com/a/45898931
namespace std {
    template <> struct tuple_size<edge> : std::integral_constant<size_t, 2> { };
    template <> struct tuple_element<0,edge> { using type = int; };
    template <> struct tuple_element<1,edge> { using type = int; };

    //解引用 auto [v,w] = e;
    template <std::size_t I>
    auto get(edge const& x) {
        if      constexpr(I == 0) return x.v;
        else if constexpr(I == 1) return x.w;
    }

    template <> struct tuple_size<edge_no_w> : std::integral_constant<size_t, 1> { };
    template <> struct tuple_element<0,edge_no_w> { using type = int; };

    template <std::size_t I>
    auto get(edge_no_w const& x) {
       // return x.v;
       static_assert(I==0,"I must eq 0!");
    }

    template <>
    auto get<0>(edge_no_w const& x) {
       return x.v;
    }
}
