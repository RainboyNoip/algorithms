// 对树进行轻重划分
//Heavy-Light Decomposition

#pragma once
#include "graph/linkList.hpp"


template<std::size_t N = maxn>
struct heavy_light_son_decomposition {
    int size[maxn]; //每个点的子树的大小
    int fa[maxn];
    int  __hson[maxn]; //每个点的重儿子

    void clear() {
        memset(size,0,sizeof(size));
        memset(__hson,0,sizeof(__hson));
    }

    template<typename GraphType,typename Edge,std::size_t V_CNT,std::size_t E_CNT>
    void init(linkList<GraphType,Edge,V_CNT,E_CNT> & e ,int root) {
        clear();
        dfs_for_hson(e,root,0);
    }

    template<typename GraphType,typename Edge,std::size_t V_CNT,std::size_t E_CNT>
    void dfs_for_hson(linkList<GraphType,Edge,V_CNT,E_CNT> & e,int u,int parent) {
        size[u] = 1;
        fa[u] = parent;
        for(int i = e.head(u) ; ~i ; i = e.next(i))
        {
            int v = e[i].v;
            if( v == parent) continue;
            dfs_for_hson(e,v,u);
            size[u] += size[v];

            //更新重儿子
            if( __hson[u] == 0 || size[v] > size[ __hson[u] ])
                __hson[u] = v;
        }
    }


    //得到点u的重儿子
    inline
    int hson(int u) const { return __hson[u];}

    //点u是否是重儿子
    //? 根结点是不是重儿子
    bool is_hson(int u) const {
        return __hson[fa[u]] == u;
    }

};
