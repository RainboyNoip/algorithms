//差分数组 用于: 多次区间增减,一次查询单点
//区间修改 转成 点修改
// 使用方法
// push(t) 不停的一个一个加入数据
// range_add(l,r,add) 区间加
// for(auto v : sub_array ){ } 遍历前缀和
//
#pragma once
#include "base/macro.hpp"


template<typename T = int , std::size_t N = maxn>
struct sub_array {
    int a[maxn];
    int cnt = 0;
    int pre=0; //前一个元素

    sub_array()
        : cnt(0),pre(0)
    {}

    void clear() {
        pre = cnt = 0;
    }

    int size() const { return cnt; }

    void push(int v) {
        a[++cnt] = v-pre;
        pre = v;
    }

    void range_add(int l,int r,int add) {
        if( l > r) return;
        a[l] += add;
        a[r+1] -= add;
    }

    T query(int r) {
        T sum = 0;
        for(int i=1;i<=r;++i){
            sum += a[i];
        }
        return sum;
    }

    //TODO,遍历前缀和
    auto begin() { return &a[1];}
    auto end()  { return &a[1+size()];}

};
