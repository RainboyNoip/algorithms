//--- 实现了队列与优先队列的数据结构
// 使用方法:
// struct node { };
// queue<node,1000> myque; 
// myque.push({1,2})
// myque.emplace_back(1,2)
// myque.size() 元素数量
// myque.empty()
// myque.front()
// myque.back()
// myque.pop_back()
// myque.pop_front()

#pragma once
#include "base/macro.hpp"

template<typename T,std::size_t N = maxn>
struct queue {
    T a[N]; //数据
    unsigned int head{0};
    unsigned int tail{0};

    void clear() { head = tail = 0;}

    queue():head{0},tail{0} { }

    inline void init() { head =tail= 0;}

    inline
    void push(const T & v) {
        a[tail++] = v;
    }

    inline
    void push(T && v) {
        a[tail++] = std::move(v);
    }

    template<typename... Args>
    inline void emplace_back(Args&&... args) {
        a[tail++] = {std::forward<Args>(args)...};
    }

    inline void pop_front() { ++head;}
    inline void pop_back() { --tail;}

    inline
    T & front() { return a[head]; }

    inline
    T & back() { return a[tail-1]; }

    inline
    std::size_t size() const { return tail - head;}

    inline
    bool empty() const { return head == tail;}

};


template<typename T,std::size_t N = maxn>
struct monotonic_queue : public queue<T, maxn>{
    // using queue<T, N>::empty();
    using Q = queue<T,N>;
    
    //符合条件就删除
    template<typename F>
    inline void remove_front(F f) {
        while( !Q::empty() && f(Q::front()))
            Q::pop_front();
    }

    template<typename F>
    inline void remove_back(F f) {
        while( !Q::empty() && f(Q::back()))
            Q::pop_back();
    }

    template<typename F>
    void push(const T & v, F f) {
        remove_back(f);
        Q::push(v);
    }

    using Q::push;
};
