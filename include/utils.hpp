#pragma once
#include <ctime>
#include <iostream>
#include <chrono>
#include <iomanip>

#include <algo/base.hpp>
#include <algo/log.hpp>


namespace rainboy {

    class Timer {
        public:
            Timer()
            : _start_time{std::clock()},
            _Wall_start{ std::chrono::high_resolution_clock::now() }
            {}
            ~Timer(){
                _end_time = std::clock();
                _Wall_end = std::chrono::high_resolution_clock::now();
                std::cerr << std::fixed << std::setprecision(2) 
                    << fg_blue << bg_green
                    << "CPU time used: "
                    << rst << fg_red << blink << blod
                    << 1000.0 * (_end_time - _start_time) / CLOCKS_PER_SEC << " ms\n"
                    << rst << fg_blue << bg_green
                    << "Wall clock time passed: "
                    << rst << fg_red << blink << blod
                    << std::chrono::duration<double, std::milli>(_Wall_end - _Wall_start).count()
                    << " ms\n"
                    << rst;
            }
        private:
            std::clock_t _start_time,_end_time;
            std::chrono::time_point<std::chrono::high_resolution_clock> _Wall_start,_Wall_end;
    };


#if __cplusplus >= 201703L

inline void log_barrier(){
    std::cout << "\n----------------------------\n\n";
}

template <typename... _Args>
void log(_Args&&... args){
    ( (std::cout << args << " "),...);
    std::cout << '\n';
}

//输出类型名 type_name<int&>() -> "int&"
template <class T>
constexpr
std::string_view
type_name()
{
using namespace std;
#ifdef __clang__
    string_view p = __PRETTY_FUNCTION__;
    return string_view(p.data() + 34, p.size() - 34 - 1);
#elif defined(__GNUC__)
    string_view p = __PRETTY_FUNCTION__;
#  if __cplusplus < 201402
    return string_view(p.data() + 36, p.size() - 36 - 1);
#  else
    return string_view(p.data() + 49, p.find(';', 49) - 49);
#  endif
#elif defined(_MSC_VER)
    string_view p = __FUNCSIG__;
    return string_view(p.data() + 84, p.size() - 84 - 7);
#endif
}

#endif
} //namespace rainboy
