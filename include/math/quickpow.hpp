#include <iostream>
//快速幂取模

template<typename T = long long>
T quick_pow(T a , T b, T mod)
{
    T &base = a;
    T ans = 1;
    if( b == 0) {
        return 1 % mod;
    }
    for( ;b; b >>=1)
    {
        if( b & 1) 
            ans = ans * base % mod; //是1就乘
        base = base * base % mod; // base增增
    }
    return ans % mod;
}

//快速乘 取模
template<typename T = long long>
T quick_mul(T a , T b, T mod)
{
    if( a == 0 || b == 0) {
        return 0;
    }
    else if( a == 1 || b == 1) {
        return (a*b) % mod;
    }

    T base = b;
    T ans = 0;
    for(; a ;a >>=1 ) {
        if( a & 1) {
            ans = (ans + base) % mod;
        }
        base <<=1; //base * 2, 2^0, 2^1,2^2 ,....
        base %= mod;
    }
    return ans % mod;
}
