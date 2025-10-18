// topsort: 拓扑排序
// 使用方法:
// TopSort<Graph_nw,100> tp;
// tp.set_graph( gh );
// tp.add_degree(1)
// tp.work(n,[](int v) { cout<< v})
#include "base/macro.hpp"
#include "data_structure/queue.hpp" //队列


template<typename Graph,int N=maxn>
struct TopSort {
    int indegree[N];
    // bool exists[N]; // 点是否存在
    queue<int,N> que_;
    int tot; // 点的数量

    Graph * graph_;

    void set_graph(Graph * g){
        graph_ = g;
    }

    void clear() {
        memset(indegree,0,sizeof(indegree));
        // memset(exists,0,sizeof(exists));
        que_.clear();
    }

    // //设置点u存在
    // template<typename... Int>
    // void set_exists(Int... args) {
    //     ((exists[args]=1),...);
    // }

    //增加点的入度
    void add_degree(int u) {
        ++indegree[u];
    }
    
    //设置点的数量
    void set_size(int n) {
        tot = n;
    }

    template<typename F>
    void work(int n,F&& f) {
        tot = n;
        for(int i =1;i<=tot;++i) {
            // if( indegree[i] == 0 && exists[i]){
            if( indegree[i] == 0){
                f(i);
                que_.push(i);
            }
        }

        while(!que_.empty()) { //队列不空
            int u = que_.front();
            que_.pop_front();

            for( auto Info : graph_->start_from_head(u))
            {
                int v = Info;
                if( --indegree[v] == 0) {
                    f(v);
                    que_.push(v);
                }
            }
        }
    }
};

