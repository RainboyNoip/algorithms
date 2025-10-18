/**
 * 倍增算法,包含RMQ的st表
 *
 * 倍增算法的核心:
 * 1. 记录信息
 *    点i后面的2^j个点的位置(不包括i)
 *      可以是[i+1,i+2^j]这个区间的信息,比如区间和,
 *      也可以相对i的2^j远的点是哪个, 比如求lca
 *      但是这些信息一定要可以合并:-> 知道区间信息就知道合并后的区间信息
 * 2. 二进制划分
 *      原理: 任何数都可以由二进制组成
 *      
 *      整个区间的右侧有一个不可达到区域x,
 *      从i点开始按"倍增"的方法跳跃,最终一定到达,最接近x区域的a点
 *      记录的信息帮助我们跳跃
 *      [ i            a][xxxxx]
 *
 *
 *
 *          2^0 2^1     2^2
 *
 *      -1---2---3---4---5---
 *           ^   ^       ^
 *           |   |       |
 * 
 *
 * 有两种跳跃的方法
 * 1. 从最大到0
 * 2. 先从0到尽可能大,然后再到0
 *
 *
 */
#include "base/macro.hpp"

//预处理,得到一个数组,a[n]的值为x:2^x <= n的最大的x
template<int N>
struct fake_log2 {
    int a[N]; // a[i] 表示 2^x <= i 的最大x
    constexpr fake_log2() {
        a[1] = 0;
        for(int i =2;i<=N;i++) {
            if(i == (1<< (a[i-1]+1)))
                i = a[i-1]+1;
            else
                i = a[i-1];
        }
    }
    constexpr int operator()(int n) {
        return a[n];
    }
};


//求最接近 n的 2^i
//也就是最高位1的位置
constexpr inline int floor_log(int n) {
    return std::__lg(n);
}

//前2^j 位置,不包括自己
inline int pre_pos(int i,int j) {
    return i - (1<<j);
}

//提取 模板类 child<size_t N> 中的N
template<template <std::size_t> class T, int N>
constexpr std::size_t extract_N(const T<N>&) { return N; }

//CRTP,Curiously Recurring Template Pattern
// drive
template<template<std::size_t> class _Drive,std::size_t N = maxn>
struct multi_double {
    using Drive = _Drive<N>; //孩子的数量
    friend Drive;

    fake_log2<N> * log2 = nullptr; // 预处理的数组指针
    static constexpr int max_log = floor_log(N);

    int f[N][max_log+1];

    /* 调用Drive类 的 merge_impl,合并 f[i][j] 的左右两半,得到f[i][j]
    * 
    *  
    *                     i+i^2^(j-1) +2^(j-1)
    *          ┌───────────────────────────┐
    *          │   i+2^(j-1)-1             │
    *    ┌─────┼──────────────────────┐    │
    *    │     │                      │    │
    *────┴─────┴──────────────────────┴────┴───────────
    * 
    */
    inline int get(int i,int j) {
        return static_cast<Drive*>(this)->merge_impl(f[i][j-1],f[i+(1<<(j-1))][j-1]);
    }

    inline void __init() {
        for(int j = 1;j<=max_log;j++) //枚举2^j
        {
            for(int i=0;i<=pre_pos(N,j);i++) {//枚举起点,是不是从0点开始比较好
                f[i][j] = get(i,j);
            }
        }
    }
    
    //初始化信息
    // 子类需要实现 get0(i) 也就是f[i][0]
    void init(){
        //init0,初始化f[i][0]的信息
        // static_cast<Drive*>(this)->init0();
        for(int i =0;i<N;i++) // < N ,因为N后面没有元素了
            f[i][0] = static_cast<Drive*>(this)->get0(i);
        __init();
    }

    //从i点开始跳跃,得到停下来的点
    // TODO 这个跳跃不好,应该从小跳
    // TODO 这个jump 什么样的情境需要
    // 子类需要实现 limit_jump(i,k) i能不能到达k这个位置
    int jump(int i) {
        for(int j = max_log;j>=0;j--)
        {
            if( !static_cast<Drive*>(this)->limit_jump(i,i+2^j) )
                i += 2^j;
        }
        return i;
    }
};

/*
//模板 --> 一个区间最大值的模板
template<std::size_t N = maxn>
struct xxx : public multi_double<xxx, N>{
    
    using multi_double<xxx,N>::f;
    using multi_double<xxx,N>::init;
    using multi_double<xxx,N>::jump;

    //实现get0
    inline int get0(int i) {
#ifdef DEBUG
        if (a == nullptr)
            throw  std::invalid_argument("not set origin  array, pls rum set_orgin_array(a[])");
#endif
        //TODO here
    }

    //实现merge_impl ,a = f[i][j-1],b = f[i+(1<<(j+1))][j-1]
    int merge_impl(int a,int b){
        return a> b? a : b;
    }

    //从i跳跃到end这个位置可以吗
    bool limit_jump(int i,int end) {

    }

    //实现查询
    int query(int l,int r) const {
        int j = floor_log(r-l+1);
        return std::max(f[l-1][j],f[pre_pos(r,j)][j]);
    }
};
*/

//rmq算法,区间最值
//rmq与上的面的倍增的区别,
template<std::size_t N = maxn>
struct rmq : public multi_double<rmq,N>{

    using multi_double<rmq,N>::f;
    using multi_double<rmq,N>::init;

    int * a = nullptr; //原数组

    //设定原数组
    template<std::size_t sz>
    void set_orgin_array(int (&arr)[sz] )
    {
        a = arr;
    }

    inline int get0(int i) {
#ifdef DEBUG
        if (a == nullptr)
            throw  std::invalid_argument("not set origin  array, pls rum set_orgin_array(a[])");
#endif
        return a[i+1];
    }

    //a,b两个区间的信息,如何合并的
    int merge_impl(int a,int b){
        return a> b? a : b;
    }

    //查询
    int query(int l,int r) const {
        int j = floor_log(r-l+1);
        return std::max(f[l-1][j],f[pre_pos(r,j)][j]);
    }

};
