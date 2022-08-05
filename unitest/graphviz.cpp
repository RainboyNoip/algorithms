#include <iostream>
#include "utils/graphviz.hpp"
using namespace DOT;
int main(){
    auto g = graphviz<DI>();
    g.setEdgeAttributes<DOT::dot_attrs::color>(dot_color::red);
    //auto dotstr = g.to_dot();
    //std::cout << 
        //dotstr
        //<< std::endl;

    auto & n1 = g.addNode(1);
    auto & n2 = g.addNode(2);
    n1.set<dot_attrs::color>(dot_color::red);
    n2.set<dot_attrs::color>(dot_color::blue);

    g.addEdge(n1, n2);


    std::cout << 
        g.to_dot()
        << std::endl;

    g.output();
    return 0;
}
