// -- 实现了 kmp 算法,时间复杂度 O(len(s) + len(a))
//-----------------------------
// 使用方法
// KMP mykmp; //定义
// char s[],a[];  定义字符串数据
// mykmp.work(s,a, [](int i){  //do something })
// 或者
// KMP kmp2;
// kmp2.set_s(s);
// kmp2.set_p(a);
// mp.work(s,a, [](int i){  //do something })
//-----------------------------
// TODO ,传递字符串
// kmp算法的核心在于 next[] 数组的实现,next数组是一个动态规划
// next[i] 表示a[i]的匹配长度,就是长度不能为i的a数组开始与a[i]结尾的最长匹配长度
//  数学描述就是: a[1,j] = a[i-j+1,i], j最大,且j != i
//
// next[i] 计算过程可以认为是一个dp的过程
// pre 是 a[i-1] 的匹配长度
// 则 next[i],一个不停失配的过程
//       = pre +1 , 如果 a[pre+1] == a[i], 
//       = pre = next[pre] 截取自己的匹配
//       = 0
//                      i-1
// kmp 是一个不停比较然后失配
//     ───|─────────────────| @
//     
//        |──a───|────|──b──| @
//               pre
//     
//                         i-1
//     ───|─────────────────| @
//     
//                   |───a──|
//                          pre

#include "base/macro.hpp"

#ifndef __HEADER_BASE_HPP__
#include <cstring>
#endif

//注意: 所有的串都从0开始
template<std::size_t N = maxn>
struct KMP {
    char * s; //s串
    char * p; //p串,s串中p串的匹配

    int len_s{-1};
    int len_p{-1};
    int next[maxn]; //p串的next
    // 注意这里next的定义:
    // next[i] = x  表示 p[i-x+1,i] 与 p[1,x],这个x个元素,最大匹配
    

    KMP() = default;
    KMP(char * s,char *p)
        :s(--s),p(--p)
    {}

    void set_s( char * _s) { len_s = -1;s = _s;}
    void set_p( char * _p) { len_p = -1;p = _p;}

    
    void init() {
        // len_s 表示没有得到len_s的值
        if( len_s == -1) len_s = strlen(s+1);
        if( len_p == -1) len_p = strlen(p+1);
        calc_p_next(); // 求p串自己的匹配
    }

    void calc_p_next() {
        int pre = next[1] = 0; // pre 上一个元素(i-1) 匹配的长度
        for(int i = 2;i<=len_p;++i) {
            while( pre > 0 && a[i] != a[pre+1] )
                pre = next[pre]; //不停的回退
            if( a[i] == a[pre+1]) pre++; // 停止后的检查
            next[i] = pre;
        }
    }

    //返回第个元素的位置
    inline char at_s(int i) const { return s[i]; }
    //返回第个元素的位置
    inline char at_p(int i) const { return a[i]; }

    //计算每一个 出现匹配的位置
    template<typename F>
    void work(char * _s,char * _p,F && f) {
        s = _s;
        p = _p;
        work(std::forward<F>(f));
    }

    template<typename F>
    void work(F && f) {
        init(); //初始化
        int pre = 0;
        for(int i =1;i<=len_s;++i)
        {
            // pre == len_p 表示上一个位置结尾已经匹配完了
            while(pre >0 && ( pre == len_p || s[i] != a[pre+1]))
                pre = next[pre];
            if( s[i] == a[pre+1]) pre++;
            //f[i] = pre; //s[i] 的a的最长匹配
            if(pre == len_p) { //匹配成功,调用位置
                f(i);
            }
        }
    }
};
