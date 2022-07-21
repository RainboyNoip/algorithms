// https://zh.wikipedia.org/wiki/%E9%93%BE%E5%BC%8F%E5%89%8D%E5%90%91%E6%98%9F
//[链式前向星及其简单应用 | Malash's Blog](https://malash.me/200910/linked-forward-star/)
/**
 * 存树与图的基础数据结构
 * 具体使用见 examples/linkList.cpp
 * 使用:
 *   1. 定义
 * _linkList e1;         //定义一个默认有 10^6个点,10^6个边的 存储结构
 * _linkList<100> e2;    //定义一个有 100个点,10^6个边的 存储结构
 * _linkList<100,100> e3;//定义一个有 100个点,100 个边的 存储结构
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

#include "base.hpp"

namespace RALGO {

//存一条边
struct edge {
    int v,w,next;

    //当做一个int时,记录的就是当前点
    operator int() { return v; }

    template <std::size_t I>
    friend auto get(edge const& x) {
        if      constexpr(I == 0) return x.v;
        else if constexpr(I == 1) return x.w;
    }
};


/**
* 说明:边的编号从0的开始
*/
template<std::size_t V_CNT,std::size_t E_CNT>
class _linkList {

private:
    
    edge e[V_CNT];
    int h[E_CNT],edge_cnt=0;

public:
    
    _linkList(){	//构造函数
        edge_cnt=0;
        memset(h,-1,sizeof(h));
    }

    //遍历点u 周围点
    template<typename U>
    void for_each(int u,U func){
        for(int i = h[u] ; i !=-1;i = e[i].next)
            func(e[i].u,e[i].v,e[i].w); //u v w
    }
    void add(int u,int v,int w=0){
        e[edge_cnt] = {v,w,h[u]};
        h[u] = edge_cnt++;
    }

    void add2(int u,int v,int w=0){
        add(u,v,w);
        add(v,u,w);
    }

    //返回以u为起点的第一条边的编号
    int head(int u) const{ return h[u]; }

    //返回第i条边的编号
    edge& operator[](int i){ return e[i]; }

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
        _linkList * self; //指向linkList的指针
        int idx;

        edgePoint(_linkList * l,int edge_idx) : self{l},idx{edge_idx} 
        {}

        bool operator!=(int a){ return idx != a;};

        edgePoint& operator++() {
            if( idx != -1) idx = self->e[idx].next;
            return *this;
        }

        edge& operator*(){
            return self->e[idx];
        }
    };
    struct EdgeIterator {
        _linkList * self; //指向linkList的指针
        int u; //哪个点周围的点
        edgePoint begin() { return {self,self->h[u]}; }
        int end(){ return -1;}
    };


    EdgeIterator edges_start_for(int u){
        return {this,u};
    }

};


using linkList = _linkList<1000005,1000005>;

} //namespace __MY_SELF__NAMESPACE__
  //

//如何 使 struct binding 支持自己的类型
//https://stackoverflow.com/a/45898931
namespace std {
    template <> struct tuple_size<RALGO::edge> : std::integral_constant<size_t, 2> { };

    template <> struct tuple_element<0,RALGO::edge> { using type = int; };
    template <> struct tuple_element<1,RALGO::edge> { using type = int; };
}
