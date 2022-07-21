/**
 * 二分图染色,
 *
 * 作用:
 *
 * 1. 判断一个图是否是二分图
 * 2. 判断一个图是否没有奇环(奇环无法形成二分图)
 * 3. 判断一个图是否没有环或只有偶环
 *
 */
#include "graph/linkList.hpp"

namespace RALGO {
    

template<std::size_t size,typename LinkList = linkList> 
struct _bipartite_graph_color 
{
private:
    linkList & _e;
    int color[size];
public:
    _bipartite_graph_color(linkList & e) : _e{e} 
    {
        //-1表示还没有颜色，就是没有访问过
        memset(color,-1,sizeof(color));
    }

    bool work(){ return dfs(1,1); }

private:
    //u上一个点，pre上一个点的颜色，颜色只能是0 or 1
    bool dfs(int u,int pre){
        color[u] = pre ^ 1;
        for(auto & e : _e.edges_start_for(u)) {
            int v = e;
            if( color[v] == -1){
                if( !dfs(v,color[u]) ) 
                    return false;
            }
            else if(color[v] == color[u])
                return false;
        }
        return true;
    }

};

using bipartile_graph_color = _bipartite_graph_color<MAXN::value, linkList>;

} // end namespace RALGO
