#include <iostream>
#include <fastIO.hpp>


int main(){
    int a,b,c;
    _in >> a >> b >> c;
    _out(a,b,c).ln();
    // std::cout << " a: " << a<< std::endl;
    // std::cout << " b: " << b<< std::endl;
    // std::cout << " c: " << c<< std::endl;
    _in.read(a,b,c);
    _out(a,b,c).ln();
    // std::cout << " a: " << a<< std::endl;
    // std::cout << " b: " << b<< std::endl;
    // std::cout << " c: " << c<< std::endl;
    return 0;
}
