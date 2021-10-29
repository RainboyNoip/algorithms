#pragma once
#include "table.hpp"

#define tdbg(...) Tools::table_debug(#__VA_ARGS__,__VA_ARGS__)
/**
 * int x=1,y=2,z=3;
 * tdbg(x,y,z);
 * --> print
 *  
 */

namespace Tools {

    template<typename... Args>
    void table_debug(std::string_view Argment,Args... args){
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
    
} // end namespace Tools

