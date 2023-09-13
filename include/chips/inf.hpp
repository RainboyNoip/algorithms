#include "base/macro.hpp"
// 使用方法
// int a = INF; // a-> 0x7ffffff 极值
// int a = NINF; //负的极值
// int a = inf; // a-> 0x3f3f3f3f 可加的极值
// char c= INF;
// double d = INF;

//得到数值的最值
struct __INF {
    template<typename T>
    constexpr operator T() const {
        return std::numeric_limits<T>::max();
    }

    template<typename T>
    constexpr bool operator==(const T oth) const
    {
        return T(*this) == oth;
    }

};

struct __NINF {
    template<typename T>
    constexpr operator T() const {
        return std::numeric_limits<T>::lowest();
    }

    template<typename T>
    constexpr bool operator==(const T oth) const
    {
        return T(*this) == oth;
    }
};

constexpr auto NINF = __NINF();
constexpr auto INF  = __INF();

//得到数值的相对最值 0x3f
struct __inf {
    constexpr operator unsigned long long() const { return 0x3f3f3f3f3f3f3f3f; }
    constexpr operator long long() const  { return 0x3f3f3f3f3f3f3f3f; }
    constexpr operator unsigned int() const { return 0x3f3f3f3f; }
    constexpr operator int() const { return 0x3f3f3f3f; }
    constexpr operator char() const { return 0x3f; }
    constexpr operator unsigned char() const { return 0x3f; }

    template<typename T>
    constexpr bool operator==(const T oth) const
    {
        return T(*this) == oth;
    }
};

constexpr auto inf = __inf();
