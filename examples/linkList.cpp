#include "graph/linkList.hpp"

int main(){
    //创建
    RALGO::_linkList<100, 100> e;

    //添加三条边
    e.add(1, 2);
    e.add(1, 3);
    e.add(1, 4);

    //遍历1
    for (auto &v : e.edges_start_for(1)) {
        std::cout << int(v) << std::endl; //v就是一条边edge,直接当成int来使用,就是v点
    }

    //遍历2
    for (auto &[v,w] : e.edges_start_for(1)) {
        std::cout << v << " " << w << std::endl; //v就是一条边edge,直接当成int来使用,就是v点
    }

    //遍历3 是基础的遍历
    for (int i = e.head(1) ;~i ;i = e[i].next) {
        int v = e[i].v,w = e[i].w;
        std::cout << v << " " << w << std::endl; //v就是一条边edge,直接当成int来使用,就是v点
    }
    return 0;
}
