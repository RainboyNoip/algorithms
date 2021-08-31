#pragma once
#include <ctime>
#include <iostream>
#include <chrono>
#include <iomanip>

#include <algo/base.hpp>
#include <algo/log.hpp>


namespace __MY_SELF__NAMESPACE__ {

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
} //namespace __MY_SELF__NAMESPACE__
