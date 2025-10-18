#include <iostream>
#include "math/great_inference.hpp"

int main (int argc, char *argv[]) {
    int ans = great_infernce(33,74);
    std::cout << "ax ≡ 1 (mod 74) -> ";
std::cout << "x ≡ " << ans << " (mod 74) \n" ;
    return 0;
}
