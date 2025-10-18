#include <iostream>
#include "base.hpp"

int arr[5] = {101,102,103,104,105};

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
    // std::cout << a << "\n";

    out.ln();
    auto tup = std::make_tuple(4,3,2,1);
    out << tup;
    out.ln();
    out.print<','>(tup);
    out.ln();

    out.print(arr, arr+5);

    //输出tuple
    return 0;
}
