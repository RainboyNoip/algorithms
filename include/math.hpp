//所有数学相关的算法
#pragma once
#include "base.hpp"


namespace __MY_SELF__NAMESPACE__ {

template<typename T>
inline T gcd(T a,T b){
    while ( b ) {
        T t = a % b;
        a = b,b = t;
    }
    return a;
}

template<typename T>
inline T lcm(T a,T b){
    return a/gcd(a,b) * b;
}

template<typename T>
T exgcd(T a,T b,T& x, T& y){
    //TODO
}




} //namespace __MY_SELF__NAMESPACE__

