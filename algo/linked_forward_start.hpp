// https://zh.wikipedia.org/wiki/%E9%93%BE%E5%BC%8F%E5%89%8D%E5%90%91%E6%98%9F
//[链式前向星及其简单应用 | Malash's Blog](https://malash.me/200910/linked-forward-star/)

#pragma once
#include <cstddef>
#include <iostream>


namespace __MY_SELF__NAMESPACE__ {

/**
* 说明:不可以有编号为0的点
* 使用: TODO
*/
template<size_t _edge_cnt=1000005,size_t _vex_cnt=200005>
struct linkedForwardStar {
    struct Itertor;
    struct edge{ 
        int v,w; edge * nxt;
        friend std::ostream& operator<<(std::ostream& __out,const edge & __e){
            __out << "v: " << __e.v;
            __out << " w: " << __e.w;
            return __out;
        }
    };
    edge e[_edge_cnt];
    edge *head[_vex_cnt]={nullptr}; size_t edge_cnt{0};

    struct Itertor {
        edge * _p_edge;
        //Itertor() :_p_edge{nullptr} {}
        Itertor(edge * __pe) :_p_edge{__pe} {}
        void operator++(){ _p_edge = _p_edge->nxt;}
        edge& operator*(){ return *_p_edge; }
        //void operator++(int){ ++*this; }
        //friend bool operator==(const Itertor &__x,const Itertor &__y){
            //return __x._p_edge == __y._p_edge;
        //}
        friend bool operator==(const Itertor &__x,decltype(nullptr)){
            return __x._p_edge == nullptr; 
        }

        Itertor& begin(){ return *this;}
        //auto end(){return Itertor{nullptr};}

        //c++17 requires
        auto end(){return nullptr;}
    };
    void add(int u,int v,int w=0){
        e[edge_cnt] = {v,w,head[u]};
        head[u] = &e[edge_cnt++];
    }
    void add2(int u,int v,int w=0){
        add(u,v,w);
        add(v,u,w);
    }

    //edge& 
    Itertor operator[](int __vex){
        return Itertor{head[__vex]};
    }
};

} //namespace __MY_SELF__NAMESPACE__
