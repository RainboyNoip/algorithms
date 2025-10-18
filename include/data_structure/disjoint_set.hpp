//并查集(Disjoint Sets)
/*----------
feature:
- 动态维护多个不相交的集合
- find(u),查找元素在哪个集合,
- merge 合并集合

----------*/
#include "base/macro.hpp"

//普通并查集,路径压缩版本
// init() : 初始每个点的为单独的集合
// find( T a) : 找到a所在的集合
// dsu[a] find(a)操作的alisa
// void merge( T a,T b) : 合并a,b所在的集合
template<typename T = int,std::size_t N = maxn>
struct Disjoint_set {
    T fa[N];
    Disjoint_set() {
        init();
    }

    // 每个点初始化自己的
    inline void init()
    {
        for(int i=0;i<N;++i) fa[i] = i;
    }

    //查找a所在的集合
    T find(const T & a) {
        if( fa[a] == a ) return a;
        return fa[a] = find(fa[a]);
    }

    //合并, a 合并到 b上
    void merge(const T& a,const T& b) {
        T ra = find(a);
        T rb = find(b);
        if( ra != rb ) fa[ra] = rb;
    }

    T operator[](const T & a) {
        return find(a);
    }

};


template<typename DIST = long long,typename T = int,std::size_t N = maxn>
struct Disjoint_set_with_w {
    T fa[N];
    DIST dis[N];
    DIST size[N]; //每个集合的大小
    Disjoint_set_with_w() {
        init();
    }

    void init() {
        memset(dis,0,sizeof(dis));
        for(int i=0;i<N;++i) fa[i] = i,size[i]=1;
    }

    T find( int x)
    {
        if( x == fa[x]) return x;
        int root = find(fa[x]);
        dis[x] += dis[fa[x]]; //计算距离的路径压缩
        return fa[x] = root;
    }

    void merge(int x,int y)
    {
        x = find(x);
        y = find(y);
        if( x == y) return;
        fa[x] = y;
        dis[x] = size[y];
        size[y] += size[x];
    }

};

