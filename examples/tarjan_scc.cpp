#include "graph/tarjan_scc.hpp"


RALGO::linkList e;
RALGO::tarjan_scc ts(e);

int main(){
    //8 6       1-------> 3------->5    
    //1 3       ^\        |        |        
    //3 5       | ------- |        |
    //5 6       |        \v        v
    //1 2       4<--------2------->6
    //4 1
    //4 6
    //3 4
    //2 4

    int m = 8 ,n = 6; //边与点的数量
    e.add(1,3);
    e.add(3,5);
    e.add(5,6);
    e.add(1,2);
    e.add(4,1);
    e.add(4,6);
    e.add(3,4);
    e.add(2,4);

    ts.work(1);
    std::cout << "color size : " << ts.color_size() << std::endl;

    //每个点所属于的强连通分量
    for(int i =1;i <=n;i++) {
        std::cout << "point :" << i << " color = " << ts.get_color(i) << std::endl;
    }

    std::cout << "get same color [3] node : " << std::endl;
    for (const auto& i : ts.get_same_color_node(3,n)) {
        std::cout << i << std::endl;
    }



    return 0;
}
