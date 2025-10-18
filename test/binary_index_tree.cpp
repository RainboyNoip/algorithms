#include "data_structure/binary_index_tree2.hpp"

int main() {
    
    binary_index_tree_base_opt::childrens chs(2);
    for( auto ch : chs) {
        std::cout << ch << "\n";
    }

    return 0;
}
