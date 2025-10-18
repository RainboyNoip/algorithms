//字符串hash
//注意:此算法从1开始计算字符串

#include "base/macro.hpp"

template<std::size_t N = maxn,int P = 1331>
struct strHash {
    using T = unsigned long long;

    //前缀hash值
    T H[maxn] = {0}; 

    // 进i位时,P位置的值
    // 例如10进制,左移0位, 1, 左移动1位,10
    T lenP[maxn] = {1}; 

    int str_len;

    inline T val(char c) {
        return c - 'a'+1;
    }

    // explicit strHash(){}
    strHash() = default;


    void init(char *s,int len) {
        str_len = 0;
        for(int i = 0;i < len;i++)
            push(s[i]);
    }

    //使用Iterator来初始化
    template<typename Iter>
    void init(Iter begin,Iter end) {
        str_len = 0;
        for( ; begin != end; ++begin )
            push(*begin);
    }

    //每一次加入一个字符
    void push(char c) {
        str_len++;
        H[str_len] = H[str_len-1] * P + val(c);
        lenP[str_len] = lenP[str_len-1] *P;
    }

    //求i到j子中的hash值
    T sub_hash(int i,int j)
    {
        return H[j] - H[i-1] * lenP[j-i+1];
    }

};
