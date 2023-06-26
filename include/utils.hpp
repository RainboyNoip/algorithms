#include "base.hpp"


//计算一个数i 前面的第m个数是多少
//包括i本身
inline
int predecessor(int  i,const int & m) {
    return i-m+1;
}

struct AdjacentNumberFinder {
    int m;

    AdjacentNumberFinder(int o)
        :m(o)
    {}

    //i前面第m个数是哪个
    inline
    int forward(int i) const{
        return i-m;
    }

    //i后面第m个数是哪个
    inline
    int backword(int i) const{
        return i+m;
    }

    friend
    int operator < (int i,const AdjacentNumberFinder & adj) {
        return adj.forward(i);
    }

    friend
    int operator > (int i,const AdjacentNumberFinder & adj) {
        return adj.backword(i);
    }
};


template<typename... T>
auto maximum(T&&... args) {
    return std::max({std::forward<T>(args)...});
}

template<typename T1,typename T2>
void upd_max(T1 & t,const T2& t2){
    if(t < t2)
        t = t2;
}

template<typename T1,typename T2>
void upd_min(T1 & t,const T2& t2){
    if(t > t2)
        t = t2;
}

//用最大的那个值更新T1
template<typename T1,typename T2,typename... T3>
void upd_max(T1 & t,const T2& t2, const T3 &... t3) {
    if(t < t2)
        t = t2;
    upd_max(t,t3...);
}


/*
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
*/
