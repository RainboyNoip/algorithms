//使用爬树法,求lca的算法

#pragma once

#include "base/macro.hpp"
#include "graph/linkList.hpp"

constexpr int get_lg_2(int num) {
    int k =0;
    while( (1<<(k+1)) <= num) k++;
    return k;
}

enum class LCA_TYPE {
    calc_len,
    no_calc_len
};

constexpr auto CALC_LEN  = LCA_TYPE::calc_len;
constexpr auto NO_CALC_LEN  = LCA_TYPE::no_calc_len;


// CALC_LEN 是否 爬树时计算长度
template<LCA_TYPE CALC = NO_CALC_LEN,std::size_t N = maxn>
struct lca_craw {

#ifdef DEBUG
    bool init_flag = false;
#endif

    const int lg;
    int dep[maxn]; //每个点的深度
    int f[maxn][get_lg_2(N)+1];
    int f_len[maxn][get_lg_2(N)+1]; //点i到2^j祖先的距离

    lca_craw() : lg(get_lg_2(N)) {}


    // template<typename G> //G这个类型必须是linkList
    template<typename GraphType,typename Edge,std::size_t V_CNT,std::size_t E_CNT>
    void init(linkList<GraphType,Edge,V_CNT,E_CNT> & e ,int root) {
        dfs(e,root,0,1); //这里的fa的参数必须是0
#ifdef DEBUG
    init_flag = true;
#endif
    }

    template<typename GraphType,typename Edge,std::size_t V_CNT,std::size_t E_CNT>
    void dfs(linkList<GraphType,Edge,V_CNT,E_CNT> & e,int u,int fa,int depth) {
        dep[u] = depth;
        f[u][0] = fa;
        // 显然u点到root路径上的点都已经求出来f[][]
        for(int j =1;j<=lg;j++) {

            f[u][j] = f[ f[u][j-1] ][j-1];
            // if constexpr (is_edge<Edge>::value) //只有有边权的时候才计算
            if constexpr ( CALC_LEN == LCA_TYPE::calc_len)
                f_len[u][j] = f_len[ f[u][j-1] ][j-1] + f_len[u][j-1];
        }
        for(int i = e.head(u) ; ~i ;i = e[i].next )
        {
            int & v = e[i].v;
            if constexpr ( CALC_LEN == LCA_TYPE::calc_len) {
                if constexpr (is_edge<Edge>::value)
                    f_len[v][0] = e[i].w;
                if constexpr (is_edge_no_w<Edge>::value)
                    f_len[v][0] = 1; //如果没有边长,则认为就长度就是1
            }
            if( v == fa) continue;
            dfs(e,v,u,depth+1);
        }
    }

    //返回a,b的值
    int __find_lca(int a,int b) {
        if( dep[a] > dep[b] ) //保证a浅b深
            std::swap(a, b);
        //使用a,b同样深
        for(int i =lg ;i>=0;--i)
            if( dep[ f[b][i] ] >= dep[a]){
                b = f[b][i];
            }

        //在同一条链上
        if( a == b) return a;

        for(int i =lg ;i>=0;--i)
        {
            if( f[a][i] != f[b][i]) ///不相同就跳
            {
                a = f[a][i];
                b = f[b][i];
            }
        }
        return f[a][0]; //返回停下来时候的父亲，就是lca
    }

    //求a,b之间路径长度,需要lca
    std::size_t __calc_path_len(int a,int b,int lca) {
        std::size_t __len = 0; //算法跑的长度

        auto calc_len = [&](int u) {
            for(int i =lg ;i>=0;--i)
                if( dep[ f[u][i] ] >= dep[lca]){
                    __len += f_len[u][i];
                    u = f[u][i];
                }
        };

        //求a到lca的值
        calc_len(a);
        //求b到lca的值
        calc_len(b);
        return __len;
    }


    //求a,b两个点的lca的值
    auto find(int a,int b) 
    {
#ifdef DEBUG
    if(!init_flag)
        throw std::invalid_argument("lca_craw must first call lca_craw::init()!");
#endif
        if constexpr ( CALC_LEN == LCA_TYPE::calc_len){
            auto lca = __find_lca(a, b);
            auto len = __calc_path_len(a, b, lca);
            return std::make_tuple(lca,len);
        }
        else 
            return __find_lca(a, b);
    }

};
