//一些常用的宏定义
#pragma once

#include <cstddef> // for std::size_t
#include <cassert>
#include <cstring>
#include <iostream>
#include <map>
#include <vector>
#include <array>
#include <deque>
#include <queue>
#include <stack>
#include <algorithm>
#include <iomanip>
#include <tuple>
#include <string_view>
#include <functional>
#include <memory_resource>

#ifdef __cpp_lib_ranges
#include <ranges>
#endif

#ifdef __cpp_concepts
#include <concepts>
#endif

using std::literals::string_view_literals::operator""sv;

#define __M_concat_II(a,b) a##b
#define __M_concat_I(a,b) __M_concat_II(#a,b)
#define __M_concat_sv(a) __M_concat_I(a,sv)


//将 "2e5" 这个的字符串转数字
constexpr int _sexp_to_number(std::string_view _sv){
    int num = 0,e = 0,i=0;
    while( i < _sv.length() && _sv[i] !='e')
        num = num*10 + _sv[i] - '0',++i;
    ++i;
    while( i < _sv.length() )
        e = e*10 + _sv[i]-'0',++i;
    while(e--) num = num*10;
    return num;
}
constexpr int add_five(int number) {
    return number + 5;
}

long long operator ""_Number(const char * str,std::size_t N){
    return _sexp_to_number(std::string_view(str,N));
}


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




#ifdef __maxn__
const int maxn = add_five(_sexp_to_number(__M_concat_sv(__maxn__)));
#elif not defined (maxn)
const int maxn = 1000007;
#endif

#ifdef __maxe__
const int maxe = add_five(_sexp_to_number(__M_concat_sv(__maxe__)));
#elif not defined (maxe)
const int maxe = 1000007;
#endif


#ifndef FOR
#define FOR(i, range) \
    for (auto i : range)
#else
    static_assert(0,"Macro FOR already defined!");
#endif

