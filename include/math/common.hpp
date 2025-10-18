//提供一下常用的数学计算


// 正数mod,像python的mod一样,结果一定是一个正数
// -1 % 5 = 4 ,原理, 0 mod 5 = 0 ,0的左边,-1 mod 5 应该是 4
// -1 // 5 = -1 , -1(商) x 5(被除数) + 4(余数) = -1(原数)
// T = ing or long long
template<typename T>
inline constexpr T py_mod(T val, T mod) {
    return ( (val % mod) + mod ) % mod;
}
