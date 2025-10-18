#include <iostream>
#include "utils/log.hpp"
#include "math/exgcd.hpp"

int main (int argc, char *argv[]) {
    int x,y;
    int a = 3;
    int b = 2;
    int gcd = exgcd(a,b,x,y);
    log(gcd);
    log(a,b,x,y);
    return 0;
}
