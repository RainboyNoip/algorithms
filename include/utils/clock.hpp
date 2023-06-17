#pragma once
#include <iostream>
#include <iomanip>
#include <chrono>
#include <string>
#include <ctime>
#include <thread>

namespace RALGO {

//定时器
struct __Timer {
    
    using ClockType = std::chrono::steady_clock;
    __Timer(){
        _start_time = ClockType::now();
    }

    //@brief 得到当前运行了多少时间
    auto
    elapsed() -> ClockType::duration
    {
        // return  double(std::clock() - _start_time) / CLOCKS_PER_SEC; 
        return ClockType::now() - _start_time;
    }

private:
    std::chrono::time_point<ClockType> _start_time;
};

struct Clock {

    Clock(std::string const & _msg,std::ostream &os = std::cerr)
        :msg(_msg),m_os(os),timer()
    {}
    
    
    Clock() :Clock("",std::cerr) {} //默认输出到std::cerr
                                
    Clock(std::ostream &os):Clock("",os)
    {}

    ~Clock(){
        tick();
    }

    void tick() {
        using namespace std::chrono;
        std::istream::fmtflags old_flags = m_os.setf( std::istream::fixed,
                std::istream::floatfield ); //保留原始的设置
        std::streamsize old_prec = m_os.precision( 6 ); // ?

        //得到运行时间
        auto Duration = timer.elapsed();

        //输出纳秒
        //输出 ms 毫秒
        //输出 秒
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(Duration);
        auto micro = duration_cast<microseconds>(Duration);
        m_os << msg << ' '
            << ms << " aka: "
            << micro << '\n';
            
            
        // m_os << timer.elapsed() << " s\n"
        //     << std::endl;

        //恢复原来
        m_os.flags( old_flags );
        m_os.precision( old_prec );

    }

private:
    __Timer timer;
    std::ostream& m_os;
    std::string msg; //输出的信息
};

} // end namespace RALGO 
