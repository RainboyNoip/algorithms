#include <iostream>
#include "base.hpp"



int main(){
    int a,b,c;
    in >> a >> b >> c;
    out.println(a,b);
    out.print(a,b);
    out << a;
    out << b;
    // out(a);
    // out(a,b,c).ln();
    // in.read(a,b,c);
    // out(a,b,c).ln();
    std::cout << a << "\n";
    return 0;
}
