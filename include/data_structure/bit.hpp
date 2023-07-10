//树状数组 binary index tree -> BIT

#include "base.hpp"

namespace binary_index_tree {
    int lowbit(int a) { return a & -a; } //每个元素的管辖范围
    inline int fa(int a) { return  a + lowbit(a);} //求a的父亲的坐标
    inline int left(int a) { return a - lowbit(a);} //a管辖范围左边的相邻的点

template<
template<typename,std::size_t> class Child,
typename T=int,std::size_t N = maxn>
struct bi_tree_base {

    using child = Child<T, N>;

    int a[N]; //存数据

    T query(int r) {
        

    }

    //查询区间[l,r]的信息
    T query(int l,int r) {

    }

    //更新pos的位置信息
    void update(int pos);
};


//求区间和

template<typename T=int,std::size_t N = maxn>
struct bit_range_sum 
{

    int a[N]; //存数据

    //求[1,r]的区间和
    T query(int r) {
        T sum = 0;
        while( r >=1) {
            sum += a[r];
            r = left(r);
        }
        return sum;
    }

    //查询区间[l,r]的信息
    T query(int l,int r) {
        return query(r) - query(l-1);
    }

    //更新pos的位置信息
    void update(int pos,int add) {
        while( pos <= N) {
            a[pos] += add;
            pos = fa(pos);
        }
    }
    
};

//逆序对
//可能需要离散化之后
//原理 : 需要知道 比a大的数有几个
// total - query(a) = 总数量 - <=a的数量
template<typename T=int,std::size_t N = maxn>
struct reverse_order_pair : 
    public bit_range_sum <T,N>
{
    using bit_range_sum<T,N>::update;
    using bit_range_sum<T,N>::query;
    
    int cnt=0; //记录存进来的数的数量

    inline
    int size() const { return cnt; }

    //push 一个元素进来
    //返回这个数和前面的元素造成的逆序对的数量
    int push(int a) {
        update(a,1);
        ++cnt;
        return cnt - query(a);
    }
};


} // end namespace bit_func


template<typename T=int,std::size_t N = maxn>
using bit_range_sum  = binary_index_tree::bit_range_sum<T, N>;

template<typename T=int,std::size_t N = maxn>
using reverse_order_pair= binary_index_tree::reverse_order_pair<T, N>;
