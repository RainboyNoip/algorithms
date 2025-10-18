// 分块算法
//问题: 区间增加,区间求和


#include "base/macro.hpp"
#include "cmath"

template<typename T =int, std::size_t N=maxn>
struct split_chunk {

    int pos[N]; //点i所在的块的位置
    int left[N]; //块i所左位置坐标
    int right[N];
    int chunk_size_; //块的大小

    int tot;
    T a[N]; //原始数组
    T sum[N]; //原始数组块i的区间和
    T add[N]; //块增加的标记

    void push(T v) {
        a[++tot] = v;
    }

    void init() {
        int n = tot;
        chunk_size_ = std::sqrt(N);
        memset(add,0,sizeof(add));
        memset(sum,0,sizeof(sum));
        //分块
        for(int i = 1;i <= chunk_size_ ;++i ) // i: 1->n
        {
            left[i] = (i-1) * chunk_size_ + 1;
            right[i] = (i) * chunk_size_;
        }
        if( right[chunk_size_] < n )
        {
            ++chunk_size_;
            left[chunk_size_] = right[chunk_size_-1]+1;
            right[chunk_size_] = n;
        }
        // 初始化 sum 与pos
        for(int i = 1;i <= chunk_size_ ;++i ) // i: 1->n
        {
            for(int j =left[i];j<=right[i];j++)
            {
                pos[j] = i;
                sum[i] += a[j];
            }
        }
    }

    //区间
    void  update(int l,int r,int d) {
        int p = pos[l];
        int q = pos[r];
        if( p == q) {
            force(l,r,d);
        }
        else {
            for(int i = p+1;i <= q-1 ;++i ) // i: 1->n
                add[i]+=d;
            force(l,right[p],d);
            force(left[q],r,d);
        }

    }

    //区间求和
    T query(int l,int r) {
        int p = pos[l];
        int q = pos[r];
        if( p == q) {
            return force_query(l,r);
        }
        else {
            T ans{};
            for(int i = p+1;i <= q-1 ;++i ) // i: 1->n
                ans += sum[i] + add[i]*(right[i]-left[i]+1);
            ans += force_query(l,right[p]);
            ans += force_query(left[q],r);
            return ans;
        }
    }

private:
    //暴力 区间增加
    inline void force(int l,int r,int d)
    {
        for(int i = l;i<=r;++i)
            a[i]+=d;
        int p = pos[l];
        sum[p] += d*(r-l+1);
    }
    
    T force_query(int l,int r) {
        T ans{};
        for(int i = l;i <= r ;++i ) // i: l->r
        {
            ans += a[i];
        }
        return ans+add[pos[l]]*(r-l+1);
    }

};

