#include "table.hpp"
#include <iostream>
using namespace Tools;

Table t;

template<typename... Args>
void pp(std::string_view Argment,Args... args){
    Table t;
    //std::cout << Argment << std::endl;
    std::vector<std::string_view> arg_names;
    while ( 1 ) {
        if( auto it =  Argment.find(",") ; it != std::string_view::npos ) {
            arg_names.emplace_back(Argment.begin(),it);
            Argment = {&Argment[it+1],Argment.size() - it-1};
            //std::cout << arg_names.back()<< std::endl;
            //std::cout << Argment << std::endl;
        }
        else  {
            arg_names.emplace_back (Argment);
            break;
        }
    }
    t.copy_row(arg_names);
    t.add_row(std::forward<Args>(args)...);
    t.print();
}

int main(){ //t.add_row(1,2,3,4,5);
    //t.add_row(1,2,3,4,5);
    //t.add_row(1,2,3,4,5);
    //t.add_row(1123124123,21231241,3,4,5);
    //t.print();
    //
    int x =1;
    int y =2;
    int a =3;
    __debug(x,y,a);

    return 0;
}
