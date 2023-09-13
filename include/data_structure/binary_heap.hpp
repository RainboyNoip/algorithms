//二叉堆: binary_heap
// 相当于已经建立好了树,每个点的位置都知道,只需要修改位置里的值
//使用
#include "base/macro.hpp"

// template<typename T,typename F,std::size_t N=maxn> //这里我换成了模板的模板参数
template<typename T,template<class T2> class F = std::greater ,std::size_t N=maxn>
struct binary_heap {
    static constexpr int root = 1;
    T val[N]; //值
    int tot=0;
    F<T> cmp_;

    inline int fa(int pos) {return pos>>1;}
    inline int lc(int pos) {return pos<<1;}
    inline int rc(int pos) {return (pos<<1)|1;}

    binary_heap() = default;

    binary_heap(F<T>&& f) :cmp_(std::move(f))
    {}

    int size() const {
        return tot;
    }

    void clear() {
        tot = 0;
    }

    bool empty() {
        return tot == 0;
    }

    //p1位置比p2优
    bool good(int p1,int p2) { return cmp_(val[p1],val[p2]); }

    void exchange(int p1,int p2) { std::swap(val[p1],val[p2]);}

    //将pos位置的值,向上调整,只要比较父亲优秀,就交换
    void up(int pos) {
        for(;pos != root; pos = fa(pos)) { //只要pos不是根
            if( good(pos,fa(pos)) )
                exchange(pos,fa(pos));
            else break;
        }
    }

    //将pos的值向下调整,因为父亲要比较两个孩子都要优
    // 找最fa,r,l 者中最优的那个,应该做fa
    void down(int pos) {
        while(  /*pos <= tot &&*/ lc(pos) <= tot) { //至少左孩子存在
            int l = lc(pos),r=rc(pos);
            if( r <= tot && good(r,l) ) l=r; // 存在右值,且右值更优秀
            if( !good(l,pos) ) break;//最优的那个没有fa优
            exchange(pos,l);
            pos=l;
        }
    }

    //插入一个值
    void push(T v) {
        val[++tot] = v;
        up(tot);
    }

    //得到堆顶
    T & top() {
        return val[root];
    }

    //移除堆顶
    void pop() {
        val[root] = val[tot--];
        down(root);
    }

    //删除pos位置的值
    void del(int pos) {
    }
};

binary_heap() -> binary_heap<int,std::greater,maxn>;

//模板的模板参数 deduction guide
template<typename T,template<class T2> class F = std::greater ,std::size_t N=maxn>
binary_heap(F<T>&&) -> binary_heap<T,F,maxn>;

// what code tricks name of this : partial deduction guide
// acording blew
//https://stackoverflow.com/questions/56351144/c17-partial-deduction-guide

// template<typename T,typename F,std::size_t N=maxn>
// binary_heap(F&&) -> binary_heap<T,F,N>;
