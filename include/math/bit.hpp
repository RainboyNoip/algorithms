//二进制操作
#include "base.hpp"

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


//表示二进制的类
template<typename T = int>
struct Bit {
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
