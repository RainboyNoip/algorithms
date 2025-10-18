// 来自 [算法学习笔记(77): 凸壳优化DP - 知乎](https://zhuanlan.zhihu.com/p/363772434)
// 凸壳优化（Convex Hull Trick）和 斜率优化 应该是一种东西,但对公式的解释不一样
template<typename T>
//TODO T 是number
// require number T
constexpr T _abs(T a) {
    return a > 0 ? a : -a;
}

// if x <0 ,return -1
// if x == 0,return 0
// if x >0 ,return 1
// number_sign(a ^ b)
//a ^ b can get a*b sign,because heightest bitset value
template<typename T>
constexpr T number_sign(T x) {
    return (x>0) - (x<0);
}


struct Fraction {
    int a,b;
    
    // 把共同符号提到a上,b一定是正值
    constexpr Fraction(int a,int b)
        : a( number_sign(a^b) * _abs(a))
        , b( _abs(b))
    {}

    bool operator<(const Fraction & oth) const {
        return a * oth.b < b * oth.a;
    }
    bool operator == (const Fraction & oth) const {
        return a * oth.b == b * oth.a;
    }
    bool operator <= (const Fraction & oth) const {
        return this->operator<(oth) || this->operator==(oth);
    }
};

constexpr int INF = 0x7fffffff;
constexpr Fraction NEGINF = {-INF,1};

//定义一条直线的表示
// y = kx + b
// b = y - kx
struct Line {
    int k; //斜率
    int b; //截距
    Fraction x = NEGINF; // X(i)
    int operator[](int x) {
        return k*x + b;
    }


};
