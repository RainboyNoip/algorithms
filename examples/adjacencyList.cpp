#include "../include/graph/adjacencyList.hpp"

using namespace rainboy;

set_memoryPool(128_mb);

int main(){
    memoryPool_init();
    adjacencyList adl(10);
    adl.addEdge(1,2);
    adl.addEdge(1,3);
    adl.addEdge(1,4);
    adl.addEdge(1,5);
    adl.addEdge(2,3);
    std::cout << "isexiet " << adl.edgeExist(1,2) << std::endl;
    std::cout << "isexiet " << adl.edgeExist(2,3) << std::endl;

    for( auto [v,w] : adl.sameVertexEdges(1)) {
        std::cout << v << std::endl;
    }
    return 0;
}
