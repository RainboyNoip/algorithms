/**
 * 
 * 提供多种LOG 的使用
 *
 * log(a,b,c) 输出
 * [#12]: a=1,b=2,c=3
 *
 * 原理见 https://cpphub.roj.ac.cn/ 奇技淫巧/宏调试输出技巧
 */

#pragma once
#include "base.hpp"

//颜色 TODO

namespace {

    using namespace std::literals;
    constexpr auto DEBUG_GREEN = "\033[1;32m"sv;
    constexpr auto DEBUG_YELLOW= "\033[1;33m"sv;
    constexpr auto DEBUG_ORANGE= "\033[1;34m"sv;
    constexpr auto DEBUG_PURPLE= "\033[1;35m"sv;
    constexpr auto DEBUG_BLUE  ="\033[1;36m"sv;
    constexpr auto DEBUG_COLOR_END = "\033[0m"sv;
}


#define __LOG_INFO__   "[" << "Ln " << __LINE__  << "]: "

#ifdef DEBUG
#define log(...) std::cerr << DEBUG_GREEN << __LOG_INFO__ << DEBUG_COLOR_END; __debug_with_arg_name(std::cerr,#__VA_ARGS__,__VA_ARGS__)
#else
#define log(...)
#endif

template<typename T1,typename... T2>
void __debug_with_arg_name(std::ostream & O , std::string_view args_str, T1&& arg1)
{

    O << args_str<< "=" << arg1 <<  '\n';
}

template<typename T1,typename... T2>
void __debug_with_arg_name(std::ostream & O , std::string_view args_str, T1&& arg1,T2&&... args) 
{
    auto p1 = args_str.find_first_of(",");
    O << args_str.substr(0,p1) << "=" << arg1  << ',';
    __debug_with_arg_name(O, args_str.substr(p1+1),std::forward<T2>(args)...);
}

