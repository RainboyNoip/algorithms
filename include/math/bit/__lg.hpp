// 求最位置1的位置
// 原理: https://stackoverflow.com/a/40436485
// 如何得到一个二进制数的最高有效位？ - Pecco的回答 - 知乎 https://www.zhihu.com/question/35361094/answer/1648676503
#include <algorithm>
template<typename T>
inline int leftPos_1(T x) {
    return std::__lg(x);
}


//inline int
// __lg(int __n)
// { return sizeof(int) * __CHAR_BIT__  - 1 - __builtin_clz(__n); }
