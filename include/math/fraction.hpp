/**
 * 分数类
 *
 * 使用方法
 * Fraction a1(1,2); 定义1/2
 * Fraction a2(2,4); 定义2/4
 * a1 < a2 //比较大小
 *
 */

#include "base.hpp"

//得到两个数乘后的正负 -1 表示负 1 表示正
// 负正得负 : -1
// 负负得正 : 1
//原理是异或
template<typename T>
requires std::is_same_v<T, int> || std::is_same_v<T, long long>
T sgn(T a,T b) {
    return (a^b) < 0 ? -1 : 1;
}

template<typename T = long long>
struct Fraction {
    T a,b; // 分子分母

    //得到a,b的乘/除 后的公共符号
    //-1 表示负, 1 表示正
    static
    constexpr
    T sgn(T a,T b) {
        return (a^b) < 0  ? -1 : 1;
    }

    static
        constexpr
        T _abs(T a) { return a < 0 ? -a : a;}

    //构造函数
    constexpr
    Fraction(T a,T b)
        : a(sgn(a,b)*_abs(a)), //a来存公共符号
        b(_abs(b))
    {}

    constexpr
    Fraction() : Fraction(1l,1l) {}

    void update(T _a, T _b) {
        a = _a;
        b = _b;
    }

    T & n() { return a; } //分子的引用
    T & d() { return b;} // 分母的引用


    bool operator==(const Fraction & oth) const
    {
        return a * oth.b ==  b * oth.a;
    }

    bool operator!=(const Fraction & oth) const
    {
        return !(*this == oth);
    }

    bool operator<(const Fraction & oth) const
    {
        return a * oth.b < oth.a * b;
    }

    bool operator>(const Fraction & oth) {
        return a * oth.b > oth.a * b;
    }

    //TODO
    Fraction operator*(const Fraction oth) const;
    Fraction operator-(const Fraction oth) const;
    Fraction operator+(const Fraction oth) const;
};

//无穷大的分数
const auto Fraction_inf = Fraction<long long>(1l,0l);
//无穷小的分数
const auto Fraction_neg_inf = Fraction<long long>(-1l,0l);

Fraction() -> Fraction<long long>;

using fraction = Fraction<long long>;
