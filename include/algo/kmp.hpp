// kmp 算法
// 使用方法
// KMP mykmp; //定义
// char s[],a[];  定义字符串数据
// mykmp.work(s,a, [](int i){  //do something })
// 或者
// KMP kmp2;
// kmp2.set_s(s);
// kmp2.set_a(a);
// mp.work(s,a, [](int i){  //do something })
// TODO ,传递字符串

#include "base/macro.hpp"

#ifndef __HEADER_BASE_HPP__
#include <cstring>
#endif

//注意: 所有的串都从0开始
template<std::size_t N = maxn>
struct KMP {
    char * s; //s串
    char * a; //a串,s串中a串的匹配

    int len_s{-1};
    int len_a{-1};
    int next[maxn]; //a串的next
    // 注意这里next的定义:
    // next[i] = x  表示 a[i-x+1,i] 与 a[0,x-1],这个x个元素,最大匹配
    

    KMP() = default;
    KMP(char * s,char *a)
        :s(--s),a(--a)
    {}

    void set_s( char * _s) { s = --_s;}
    void set_a( char * _a) { a = --_a;}

    
    void init() {
        if( len_s == -1) len_s = strlen(s);
        if( len_a == -1) len_a = strlen(a);
        init_next();
    }

    void init_next() {
        int pre = next[1] = 0;
        for(int i = 2;i<=len_a;++i) {
            while( pre > 0 && a[i] != a[pre+1] )
                pre = next[pre]; //不停的回退
            if( a[i] == a[pre+1]) pre++;
            next[i] = pre;
        }
    }

    //返回第个元素的位置
    inline char at_s(int i) const { return s[i-1]; }
    //返回第个元素的位置
    inline char at_a(int i) const { return a[i-1]; }

    //计算每一个 出现匹配的位置
    template<typename F>
    void work(char * _s,char * _a,F && f) {
        s = --_s;
        a = --_a;
        work(std::forward<F>(f));
    }

    template<typename F>
    void work(F && f) {
        init();
        int pre = 0;
        for(int i =1;i<=len_s;++i)
        {
            while(pre >0 && ( pre == len_a || s[i] != a[pre+1]))
                pre = next[pre];
            if( s[i] == a[pre+1]) pre++;
            //f[i] = pre; //s[i] 的a的最长匹配
            if(pre == len_a) {
                f(i);
            }

        }
    }
    
    
};
