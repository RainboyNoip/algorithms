#pragma once
#include <random>

namespace __random {
    
struct Random {
    using ll = long long;
    std::random_device rd;
    std::mt19937 engine{rd()};
    std::uniform_int_distribution<long long> dis; // in [0,0x7fffffffffffffff]
    Random(){}
    Random(ll l,ll r){ dis = std::uniform_int_distribution<long long> (l,r); }

    int operator()(){ return dis(engine); }
    ll operator()(ll l,ll r){ return l == r ? l : dis(engine) % ( r-l+1 ) + l; }

    //Random create(ll l,ll r){ return Random(l,r); } //工厂模式
} /*RND*/;

} // end namespace __algo


//随机整数生成器
__random::Random RND;
