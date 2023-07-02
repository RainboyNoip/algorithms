//生成随机树

#pragma once
#include "utils/random/random.hpp"

namespace __random {
    
struct tree {
    int * a; //记录每个点的父亲的数组
    int node_cnt;
    int root;
    explicit tree(int n)
        :node_cnt(n)
    {
        a = new int[n+5]; //申请内存
        root = RND(1,node_cnt); //根
        random();
    }

    //在数组a中生成随机的点的关系
    void random() {
        for(int i=2;i<=node_cnt;++i){
            int fa = RND(1,i-1); //这个点的父亲
            a[i] = fa;
        }
    }

    ~tree() {
        delete[] a; //释放内存
    }

    struct Iterator {
        int idx; // now index of array a
        int * a; // pointer of array that record relation between father and child

        std::tuple<int,int> operator*() const {
            return std::make_tuple(a[idx],idx);
        }

        bool operator==(const Iterator & it) const {
            return idx == it.idx && a == it.a;
        }

        bool operator!=(const Iterator & it) const {
            return idx != it.idx || a != it.a;
        }

        Iterator & operator++() {
            ++idx;
            return *this;
        }
    };

    auto begin() const {
        return Iterator{2,a};
    }

    auto end() const {
        return Iterator{node_cnt+1,a};
    }
};


//带有边权的树
struct tree_w {
    
};

} // end namespace __random
