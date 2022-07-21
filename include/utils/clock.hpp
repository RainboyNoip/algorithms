#pragma once
#include <iostream>
#include <iomanip>
#include <chrono>
#include <ctime>
#include <thread>

struct Timer {
    
    Timer(){
        _start_time = clock();
    }

    double elapsed() {
        return  double(std::clock() - _start_time) / CLOCKS_PER_SEC; 
    }
private:
    std::clock_t _start_time;
};

struct Clock {
    
    Clock() :Clock(std::cerr) {}
    Clock(std::ostream &os):timer(),m_os(os){}

    ~Clock(){
        std::istream::fmtflags old_flags = m_os.setf( std::istream::fixed,
                std::istream::floatfield );
        std::streamsize old_prec = m_os.precision( 6 ); // ?

        m_os << timer.elapsed() << " s\n"
            << std::endl;
        m_os.flags( old_flags );
        m_os.precision( old_prec );
    }
private:
    Timer timer;
    std::ostream& m_os;
};
