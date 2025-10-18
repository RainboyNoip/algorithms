#pragma once
#include "utils/table.hpp"

//TODO log(a,b,c) -> a = ? ,b = ? , c= ?

// #define log(...) { \
//     fprintf(stderr,"In [ %s ],At line [ %d ]\n",__func__,__LINE__); \
//     fprintf(stderr,__VAR_ARGS__); \
//     fprintf(stderr,"\n"); \
// }

template<char splitChar = ' ',typename first,typename ... Args>
void log_impl(first&& _f,Args&& ... _args){
    std::cerr << _f << splitChar<< " ";
    log_impl<splitChar>(std::forward<Args>(_args)...);
}

template<char splitChar = ' ',typename Args>
void log_impl(Args&& _args){
    std::cerr << _args << "\n";
}

#define log(...) log_impl(#__VA_ARGS__,...)

#define dbg_one(one)   std::cerr << #one " = " << one << std::endl
#define tdbg_one(one)  std::cerr << Tools::Table (#one,one) << std::endl
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

