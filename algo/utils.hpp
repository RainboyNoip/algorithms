#pragma once
#include <ctime>
#include <iostream>
#include <chrono>
#include <iomanip>

#include <algo/base.hpp>


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
                std::cerr << std::fixed << std::setprecision(2) << "CPU time used: "
                    << 1000.0 * (_end_time - _start_time) / CLOCKS_PER_SEC << " ms\n"
                    << "Wall clock time passed: "
                    << std::chrono::duration<double, std::milli>(_Wall_end - _Wall_start).count()
                    << " ms\n";
            }
        private:
            std::clock_t _start_time,_end_time;
            std::chrono::time_point<std::chrono::high_resolution_clock> _Wall_start,_Wall_end;
    };
} //namespace __MY_SELF__NAMESPACE__