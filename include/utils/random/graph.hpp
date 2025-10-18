//生成随机图
// n个点m条边的无向图,且无重边,无自环
// 数据保证 5<=n <= n*n(-1)/4
#pragma once
#include "base/fastIO.hpp"
#include "utils/random/random.hpp"

#include <set> //使用集合判重复

namespace __random {

struct graph {

    using edge = std::pair<int,int>;
    using set = std::set<edge>;
    
    static constexpr const int MAX_E = 1000005;
    edge e[1000005];
    set s;
    int node_size;
    int edge_cnt;


    //生成一个n个点,m条边的随机图
    explicit graph(int n,int m = 0)
    {
        init(n,m);
    }


    void clear() {
        s.clear();
        node_size = 0;
        edge_cnt = 0;
    }

    void make_graph(int n,int m=0) {
        init(n,m);
        make_graph();
    }

    void make_graph() {
        //生成一个树保证联通
        for(int i = 2;i <= node_size;++i ) // i: 1->n
        {
            int fa = RND(1,i-1);
            e[i-1] = std::make_pair(fa,i);
            s.insert(e[i-1]);
            s.insert(std::make_pair(i,fa));
        }

        // 再生成剩余的边
        for(int i = node_size;i<=edge_cnt;i++) {
            int x,y;
            do {
                x = RND(1,node_size);
                y = RND(1,node_size);
                if( x == y) continue;
                if( s.find(std::make_pair(x,y)) != s.end() )
                    continue;
                break;
            }while(1);

            e[i] = std::make_pair(x,y);
            s.insert(e[i]);
            s.insert(std::make_pair(y,x));
        }
        std::random_shuffle(e+1,e+edge_cnt+1);
    }

private:
    void init(int n,int m =0)
    {
        clear();
        node_size = n;
        if( m == 0) {
            int MAX = n*(n-1)/4;
            if(MAX > MAX_E)
                MAX = MAX_E;
            edge_cnt = RND(n, MAX);
        }
        else
            edge_cnt = m;
    }
};

}

template<>
void fast_out::println<__random::graph>(__random::graph & gh) {
    for(int i =1 ;i <= gh.edge_cnt;i++) {
        println(gh.e[i].first,gh.e[i].second);
    }
}
