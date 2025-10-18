/*---
{
"info":"边集数组",
"word":"edgeArray",
"expand":"edgeArray<MAXN::value,MAXE::value> ea;",
"user_data":"ralgo"
}
---*/
/**
 * 边集数组,主要给kruskal算法使用
 * add() 添加边
 * sort 排序
 * for(auto &[u,v,w] : edgeArray ) {
 *  
 * }
 */

#include "base.hpp"

namespace RALGO {

template<std::size_t V_CNT,std::size_t E_CNT>
struct edgeArray{
    struct edge {int u,v,w;} e[E_CNT];
    int edge_cnt=0;
    void add(int u,int v,int w=0){ e[edge_cnt] = {u,v,w,}; }
    void sort(){
        std::sort(e,e+edge_cnt,[](edge &e1,edge& e2){ return e1.w < e2.w; });
    }

    edge* begin() { return &e[0]; }
    edge* end() { return &e[edge_cnt]; }

};

//using edgeArray = _edgeArray<1000005,1000005>;


}
