#include "../include/memory.hpp"

using namespace rainboy;
using string = std::pmr::string;

set_memoryPool(128_mb);

int main(){
    memoryPool_init();
    std::cout << 
        128_mb
        << std::endl;
    string s1("short s long long long long long",std::pmr::get_default_resource());
    return 0;
}
