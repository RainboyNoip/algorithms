#include <iostream>
#include <random>

// random 类,使用 default_random
struct RND {
    using ll = long long;
    std::random_device rd;
    std::default_random_engine engine;

    RND() 
    : engine(rd())
    {}

    //产生一个[l,r] 之间的随机数
    ll operator()(int l ,int r) {
        return engine() % (r-l+1) + l;
    }
}rnd;


//pr(1,2,3,4);输出
template<typename... T>
void prln(T&&... args){
    ( (std::cout << args<<" "),...);
    std::cout << "\n";
}

template<typename... T>
void pr(T&&... args){
    ( (std::cout << args<<" "),...);
}

int main (int argc, char *argv[]) {
    int n = 8;
    int k = 3;
    prln(n,k);
    for(int i = 1;i <= n ;++i ) // i: 1->n
    {
        int t = rnd(1,10);
        pr(t);
    }
    return 0;
}

