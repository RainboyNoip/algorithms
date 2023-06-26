//并查集(Union-Find Disjoint Sets, 简称UFDS)
#include "base.hpp"


//普通并查集
template<typename T = int,std::size_t N = maxn>
struct ufds {
    T fa[N];
    //TODO
    //
    ufds() {
        init();
    }

    inline void init()
    {
        for(int i=0;i<N;++i)
            fa[i] = i;
    }

    //查找a所在的集合
    T find(const T & a) {
        if( fa[a] == a ) return a;
        return fa[a] = find(fa[a]);
    }

    //合并
    void merge(const T& a,const T& b) {
        T ra = find(a);
        T rb = find(b);
        if( ra != rb )
            return fa[ra] =rb;
    }

    T operator[](const T & a) {
        return find(a);
    }

};



