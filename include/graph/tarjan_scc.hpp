/**
 * tarjan_scc 用tarjan 求 Strongly Connected Components，SCC,强连通分量的算法
 * 判断一个图是否为强连通以及找到一个图强连通分量只需要线性时间（Θ(V + E)）
 *
 * 一句话核心: 在dfs中不能回到更早点的点是强连通分量所形成子树的根
 *
 *  tarjan_scc 使用
 *
 *  定义
 *  _tarjan_scc<100,linkList> tscc1;
 *  tarjan_scc tscc2; //默认大小的
 *
 * // linkList 添加边之后
 * for( ... ) 
 *      e.add
 *  
 *  tscc1.work(1); //从1开始计算
 *
 *  tscc1.color_size()  //一共有 强连通分量
 *  tscc1.get_color(i)  //点i的颜色
 *  tscc1.get_same_color_node(1,n) // 同一具颜色的点的 vector 集合
 *  
 */

#pragma once
#include "linkList.hpp"

namespace RALGO {

template<std::size_t size,typename LinkList = linkList> 
struct _tarjan_scc {
    
private:
    int dfn[size];  // 每个点的编号
    int low[size];  // 点能回到的更早点的编号
    int color[size];// 点的颜色,也就是这个点所属的SCC的编号
    int dfn_cnt;    // 计算编号用
    int color_cnt;  // 计算颜色编号用

    int stack[size],shead;//维护的栈 ,栈的大小
    bool in_stack[size];  //点是否在栈内,是否是正在访问的点
    inline int pop() { 
        int t = stack[--shead];
        in_stack[t] = 0;
        return t;
    }
    inline void push(int a) { 
        in_stack[a] = 1;
        stack[shead++] = a;
    }

private:
    LinkList & _e; // linkList的引用

    //tarjan_dfs
    void dfs(int u=1) {
        dfn[u] = low[u] = ++dfn_cnt;
        push(u);
        for(auto & e : _e.edges_start_for(u)) {
            int v = e;
            if(!dfn[v]) { //没有访问过
                dfs(v);
                low[u] = std::min(low[u],low[v]);//更新low
            }
            else if( in_stack[v]) { //反祖边,节点v在栈内
                low[u] = std::min(low[u],low[v]);//更新low
            }
        }
        if( dfn[u] == low[u]) {
            color_cnt++;
            int t = -1;
            do {
                t = pop();
                color[t] = color_cnt;
            }while( t !=u);
        }
    }

public:
    _tarjan_scc(LinkList & e) 
        :dfn_cnt(0), color_cnt(0), shead(0),in_stack{0},
        _e{e}
    {}

    inline void work(int u){
        dfs(u);
    }

    //某个点的强连通分量的编号
    int get_color(int a) { return color[a];}
    //两个点是否是同一个强连通分量
    bool is_same_color(int a,int b) { return color[a] == color[b]; }

    //得到强连通分量的数量
    int color_size() { return color_cnt;}

    //得到某个强连通分量的所有点
    //a 颜色,强连通分量编号
    //n 一共有多少个点
    std::vector<int> get_same_color_node(int a,int n){
        std::vector<int> v;
        for(int i = 1;i <=n;i++) {
            if( color[i] == a) v.push_back(i);
        }
        return v;
    }

};

using tarjan_scc = _tarjan_scc<1000005, linkList>;

} // end namespace RALGO

