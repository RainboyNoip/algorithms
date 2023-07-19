//单数组实现的邻接表
//类似linkList,区间就是,值不是edge
#pragma once
#include "base/macro.hpp"

template<typename T,std::size_t V_CNT = maxn,std::size_t TOT = maxe>
struct adjacencyList {
private:
    inline void __next(int head) {
        nxt[cnt] = h[head];
        h[head] = cnt;
        ++cnt;
    }
public:
        
    int h[V_CNT]; //表头
    T mem[TOT];   // 内存池
    int nxt[TOT]; // next数组,nxt[i] ,给同表头的下一下数据
    int cnt;      // 内存池计数

    adjacencyList() {
        clear();
    }

    //清空
    inline void clear() {
        cnt = 0;
        memset(h,-1,sizeof(h));
    }

    inline void push(int head,T && val) {
        mem[cnt] = std::move(val);
        __next(head);
    }

    inline void push(int head,const T & val) {
        mem[cnt] = val;
        __next(head);
    }

    //返回以u为起点的第一条数据的编号
    int head(int u) const { return h[u];}
    //总的数据数
    int size() const { return cnt;}

    T & operator[](unsigned int i) {
        return mem[i];
    }
    
    //下一条同head的数据的编号
    int next(int idx) const {
        return nxt[idx];
    }

    struct memIterator {
        adjacencyList * self; //指向adjacencyList的指针
        int idx; //数据下标
        memIterator(adjacencyList * p,int _idx)
            : self(p),idx(_idx)
        {}

        memIterator & operator++() {
            if(idx != -1) idx = self->next(idx);
            return *this;
        }

        bool operator!=(int a) { return idx !=a;}
        bool operator!=(const memIterator & a) { return idx !=a.idx;}

        T & operator*() { return self->mem[idx]; }
    };

    //一个中间对象,提供begin,end 函数
    struct mems {
        adjacencyList * self;
        const int u;
        mems(adjacencyList *p,int _u)
            :self(p),u(_u)
        {}

        memIterator begin() const {
            return memIterator(self,self->head(u));
        }
        int end() { return -1;}

    };

    // 返回同起点数据的迭代器
    auto start_from_head(int u) {
        return mems(this,u);
    }

};
