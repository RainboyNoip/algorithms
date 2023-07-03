//二进制操作
#include "base.hpp"

#include <limits>
#include <type_traits>
#if __has_include(<version>)
#include <version>
#ifdef __cpp_lib_bitops
#include <bit>
#endif
#endif

//基础的bit操作

//a的第pos位设为1
template<typename T = int>
T set_at_pos(T a , T pos){
    return a | (1 <<pos);
}

//a的第pos位设为0
template<typename T = int>
T clear_at_pos(T a , T pos){
    return a & ~(1 <<pos);
}

//a的第pos位取反
template<typename T = int>
T toggle_at_pos(T a , T pos){
    return a ^ (1 <<pos);
}

//保留后k位,其它
template<typename T = int>
T keepLast(T a , T k){
    return a & ((1<<k)-1);
}

//第k位的值
template<typename T = int>
T bit_at_pos(T a , T k){
    return (a>>k) & 1;
}


//清除最后一个1
//11,000 & 10,111 = 10,000
template<typename T = int>
T clear_last(T a){
    return a & (a-1);
}


//最低位1 后面有多少个0
template<typename T = int>
T count_bit_trail_zero_buildin(T a){
    if constexpr (std::is_same_v<int, T> || std::is_same_v<T,unsigned int>)
        return __builin_ctz(a);
    else
        return __builin_ctzll(a);
}

//最低位1 后面有多少个0
template<typename T = int>
T count_bit_trail_zero(T a){
    int count = 0;
    for( ; (a & 1) == 0; a>>=1 )
        count++;
    return count;
}


//一共有多少个1
template<typename T = int>
T count_bit_build(T a){
    if constexpr (std::is_same_v<int, T> || std::is_same_v<T,unsigned int>)
        return __builin_popcount(a);
    else
        return __builin_popcountll(a);
}

//一共有多少个1
template<typename T = int>
T count_bit(T a){
    int count = 0;
    for( ; a; a = clear_last(a) )
        count++;
    return count;
}


// 保留最低位的1,其它置0
// 111000 -> 001000
template<typename T>
inline T lowbit(T x) {
    return x & (-x);
}

// 求最位置1的位置
// 原理: https://stackoverflow.com/a/40436485
// 如何得到一个二进制数的最高有效位？ - Pecco的回答 - 知乎 https://www.zhihu.com/question/35361094/answer/1648676503
template<typename T>
inline int leftPos_1(T x) {
    return std::__lg(x);
}




//表示二进制的类
struct Bit {
template<typename T = int>
    T number;

    Bit(T v = 0)
        : number(v)
    {}

    inline void set(int pos) {
        number = set_at_pos(number, pos);
    }
    inline void reset(int pos) {
        number = clear_at_pos(number, pos);
    }

    inline void clear(int pos){
        number = clear_at_pos(number, pos);
    } 

    operator T() const { return number; }

    T to_number() const { return T(*this);}

    bool is_1(int pos) const {
        return bit_at_pos(number, pos);
    }

    bool is_0(int pos) const {
        return bit_at_pos(number, pos) == 0;
    }
};


// 代码来自 https://www.zhihu.com/question/35361094/answer/1648810477
// 求最高位
template <typename T> int high_bit(T x)
{
#ifdef __cpp_lib_bitops
    using UT = std::make_unsigned_t<T>;
    return std::numeric_limits<UT>::digits - std::countl_zero(UT(x)) - 1;
#else
    auto ux = std::make_unsigned_t<T>(x);
    int lb = -1, rb = std::numeric_limits<decltype(ux)>::digits;
    while (lb + 1 < rb)
    {
        int mid = (lb + rb) / 2;
        if (ux >> mid)
        {
            lb = mid;
        }
        else
        {
            rb = mid;
        }
    }
    return lb;
#endif
}


//子集生成算法
template<typename F>
void generateSubsets(int u ,F&& f) {
    for (int s = u; s; s = (s - 1) & u)
    {
        f(s);
    }
}
