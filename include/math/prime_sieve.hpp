//素数筛法
#include "base/macro.hpp"


template<std::size_t N = maxn>
struct Euler_sieve {
    bool notp[N];
    int primes[N]; //存素数
    int m; //素数的个数

    //筛n以内的素数
    void init(int n = N) {
        memset(notp,0,sizeof(notp));
        m = 0;
        for(int i=2;i<=n;i++)
        {
            if(!notp[i]) primes[++m] = i; //存下素数
            for(int j =1;j<=m;j++)
            {
                //超过n的范围
                // if( i*primes[i] > n)
                if( primes[i] > n/i) break;
                if( i % primes[j] ) break; //是i的因子
                notp[i*primes[j]] = 1;  //标记
            }
        }
    }

    struct Iterator {
        int idx;
        int * p;
        int operator*() {
            return p[idx];
        }

        Iterator & operator++() {
            ++idx;
            return *this;
        }

        bool operator!=(const Iterator & oth) {
            if( p != oth.p)
                return true;
            if( oth.idx == 0) //特殊判断
                return false;
            return idx != oth.idx;
        }

    };

    auto begin() {
        return Iterator{1,&primes};
    }

    auto end() {
        return Iterator{m,&primes};
    }

};
