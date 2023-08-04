//二进制操作
#include "base/macro.hpp"

#include <climits>
// require c++20
// https://en.cppreference.com/w/cpp/header/bit
#ifdef __cpp_lib_bitops 
#include <bit>
#endif


//子集生成算法,模板
/*
template<typename F>
void generateSubsets(int u ,F&& f) {
    for (int s = u; s; s = (s - 1) & u)
    {
        f(s);
    }
}
*/

//子集生成算法
template<typename T= unsigned int>
struct bit_sub_sets {
    T num;

    explicit bit_sub_sets(T num) : num{num}
    {}

    struct Iterator {
        T org; // 原数字
        T now; // 现在的数字
        

        bool operator== (const Iterator & oth) const { return now == oth.now;}
        bool operator!= (const Iterator & oth) const { return !(*this == oth);}

        Iterator & operator++() {
            now = (now-1) & org;
            return *this;
        }

        T operator*() const { return now; }

    };

    auto begin() const { return Iterator{num,num};}
    auto end() const { return Iterator{num,0};}
};

//表示二进制的类
template<typename T = unsigned int>
struct Bit {
    T num_;

    explicit Bit(T v = 0) : num_(v)
    {}

    // 转换成 T 类型
    operator T() const { return num_; }
    T to_num_() const { return T(*this);}

    // 1. 位置i置1
    Bit & set(int i) { num_ |= (1<<i);  return *this; }

    // 2. 位置i置0
    Bit & clr(int i) { num_ &= ~(1<<i); return *this;}

    // 3. 位置i toggle
    Bit & toggle(int i)  { num_ ^= (1<< i); return *this;}

    // 4. 使最后连缀i位为1,其它置0
    Bit & last(int i) { num_ = (1<<i)-1; return *this;}

    // 5. 保留最后i位不变,其它置0
    Bit & keep_last(int i) { num_ &= ((1<<i)-1); return *this;}

    // 6. 第i位是0还是1
    bool at(int i) {return (num_>>i) & 1;}

    // 7. lowbit,保留最后一个1,其它位置0
    Bit & lowbit(int i ) { num_  &= (-num_); return *this;}

    // 8. 最后一位1置0
    Bit & clr_last(int i ) { num_ &= (num_-1); return *this;}

    // 9. 最后一位1后面有多少个0
    int countl_zero() const {
#ifdef __cpp_lib_bitops
        return std::countl_zero(num_);
#else
        if constexpr (std::is_same_v<int, T> || std::is_same_v<T,unsigned int>)
            return __builtin_ctz(num_); // TODO 在clang下测试
        else
            return __builtin_ctzll(num_);
#endif
    }
    // 10. 计算总共有多少个1
    int pop_count() const {
#ifdef __cpp_lib_bitops
        return std::popcount(num_);
#else
    if constexpr (std::is_same_v<int, T> || std::is_same_v<T,unsigned int>)
        return __builin_popcount(num_);
    else
        return __builin_popcountll(num_);
#endif
    }

    // 11. 是否是子集
    bool is_sub(const T & s) {
        return ( s | num_) == num_;
    }

    // 12. 是否没有交集
    bool is_xor(const T & s) {
        return (s & num_) == 0;
    }

    // 13 求state的补集
    Bit complement_set(T state) const {
        T x = num_ & state; //先求交集
        T y = num_ ^ x; // 对它相同的部分进行清0
        return Bit<T>(y);
    }

    // 13 求交集
    // return s & num_

    // 11. TODO other 
    // has_single_bit
    // count

    //是否全是1
    bool all () const { return num_ == ~T(0); }
    // 是否含有1
    bool any()  const{ return num_ != 0;}
    // 是否全是0
    bool none()  const{ return num_ == 0;}

    //求最高的1的位置,like std::__lg
    int lg() const {
#ifdef __cpp_lib_bitops
    using UT = std::make_unsigned_t<T>;
    return std::numeric_limits<UT>::digits - std::countl_zero(UT(num_)) - 1;
#elif __has_builtin( __builtin_clz)
        // explain: code from here : https://stackoverflow.com/a/40436485
        auto pos = sizeof(T) * CHAR_BIT  -__builtin_clz(num_) -1;
        return pos;
#else

        // 代码来自 https://www.zhihu.com/question/35361094/answer/1648810477
        auto ux = std::make_unsigned_t<T>(num_);
        int l = std::numeric_limits<decltype(ux)>::digits-1;
        int r = 0;
        //使用二分查找来查询
        while( l > r) {
            int mid = (l+r) >> 1;
            if( (ux >> mid) == 0)
                l = mid-1;
            else
                r = mid;
        }
        return l;
#endif
    }

    //求最接近 <=num_,又是2的指数的那个数
    T floor() const {
    //TODO check num_ not eq 0
#ifdef __cpp_lib_int_pow2
    if constexpr (std::unsigned_integral<T>)
        return std::bit_floor(num_);
#else
    return 1 << lg();
#endif
    }

    auto sub_sets() const // 子集生成
    {
        return bit_sub_sets<T>(num_);
    }
};

template<typename T>
Bit(T) -> Bit<std::make_unsigned_t<T>>;

