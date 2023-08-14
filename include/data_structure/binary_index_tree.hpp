//树状数组 binary index tree -> BIT
#pragma once
#include "base/macro.hpp"

namespace binary_index_tree {
    int lowbit(int a) { return a & -a; } //每个元素的管辖范围
    inline int fa(int a) { return  a + lowbit(a);} //求a的父亲的坐标
    inline int left(int a) { return a - lowbit(a);} //a管辖范围左边的相邻的点
} // end namespace binary_index_tree

// 1. 单点增减,区间求和
// 2. 求逆序对

// 3 区间修改,单点查询, --> 基于差分数组
// 4 区间修改,区间查询, --> 基于差分数组

// 5. 区间最值, 末尾添加很快
// 核心思想, 对于x来说,它只能由它的孩子来更新,那么如何去求点x的孩子呢?
// c + lowbit(c) = x ,则c是x的孩子
// x - 2^0,x-2^1... x-2^k ,2^k < lowbit(x)
// 核心代码:
// bit_range_max<1000> myrange;
// - 建立 myrange.push(1);
// - 建立 myrange.push(2);
// - 建立 myrange.push(3);
// - 建立 myrange.push(5);

template<std::size_t N =maxn>
struct bit_range_max {
    using ll = long long;
    ll a[N]; //原数组
    ll c[N];
    int size_{0};

    void clear() { size_ = 0;}

    int size() const { return size_;}


    //向末尾添加一个元素
    void push_back(ll val){
        size_++;
        c[size_] = a[size_] = val;
        update_by_child(size_);
    }

    //同时push_back 多个值
    template<typename... Args>
    // std::enable_if_t<
    // std::is_same_v<ll,ll>
    // std::conjunction_v<std::is_same_v<ll,ll>>
    // ,int> = 0>
    void push_back(ll val ,Args... args){
        push_back(val);
        push_back(args...);
    }

    
    // 返回值 : 是否更新
    inline bool update_by_child(int pos) {
        c[pos] = a[pos]; // 先等于自己的直接点
        ll lb = binary_index_tree::lowbit(pos);
        bool update_flag = 0;
        for(int i = 1; i < lb; i<<=1)
            if( c[pos] < c[pos - i] )
                c[pos] = c[pos - i],update_flag = 1;

        return update_flag;

    }

    //更新某个位置的值
    void update(int pos, ll val) {
        //1. 改自己的值
        a[pos] = val;
        //2. 用孩子来更新自己
        update_by_child(pos);
        //3. 不停去更新父亲
        using binary_index_tree::fa;
        for( pos = fa(pos); pos <= size_; pos = fa(pos))
        {
            if( !update_by_child(pos))
                // break;
                ;
        }
    }

    //得到[l,r] 之间最大值
    int max(int l,int r) {
        ll res = -1;
        while( l <= r) {
            int nl = binary_index_tree::left(r)+1;
            if( nl >=l) {
                if( res < c[r]) res = c[r];
                r = nl-1; //下一个求解区间
            }
            else { // nl < l
                if( res < a[r]) res = a[r];
                r--;
            }
        }
        return res;
    }

    //得到[x,y] 之间最大值的位置
    //注 : 如何有多个最大值一样,这是个靠后最大值的位置
    int max_pos(int x,int y) {
        if( x > y) return -1; //-1 表示不可能的位置
        ll res = -1;
        int pos = y;
        while( x <= y) {
            int nx = binary_index_tree::left(y)+1;
            if( nx >=x) {
                if( res < c[y]) res = c[y],pos=y;
                y = nx-1; //下一个求解区间
            }
            else { // nx < x
                if( res < a[y]) res = a[y],pos=y;
                y--;
            }
        }

        // 检查pos具体是哪个位置
        int lb = binary_index_tree::lowbit(pos);
        while(  lb != 1) { //说明有孩子
            //找到最左边的同样大的孩子
            int tpos=pos;
            if( a[pos] == res) break;// 从0开始先从自己比较,这样可以避免错误
            for(int i =1 ;i< lb ;i <<= 1) { 
                if( pos - i < x) continue;//应该在[x,y]之间
                if(c[pos - i] == res){ // 如果为最大值
                    tpos = pos-i; //最大值的位置
                }
            }
            if( pos == tpos ) break; //没有被孩子更改,那pos位置就是最大的
            pos = tpos;
            lb = binary_index_tree::lowbit(pos);
        }
        // if( a[pos] == res) //这里不用写,因为如果不是孩子,好就是自己
        //     pos = pos;
        return pos;
    }

};
