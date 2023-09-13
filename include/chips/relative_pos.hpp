//相对位置的计算
// 1. int dis_ex(i,j)
// 2. int dis_in(i,j)
// 3. relative_pos(3).next_ex(4) 3 后面4个位置,不包括3
// 3. relative_pos(3).pre_in(4) 3 前面4个位置,包括3
#pragma once

#include <utility>

// 求i到j的之间的距离,不包括j
inline int dis_ex(int i,int j){
    if( i > j) std::swap(i,j);
    return j-i;
}

// 求i到j的之间的距离,包括j
inline int dis_in(int i,int j){
    return dis_ex(i,j)+1;
}

//相对位置的计算,
// pos 后面第i个位置是哪个,包括和不包括pos
// pos 前面第i个位置是哪个,包括和不包括pos
struct relative_pos {
    int pos; 

    explicit relative_pos(int pos) 
    :pos{pos}
    {}

    //沿着dir的方向走n步
    inline int base_ex(int n,int dir) {
        return pos+n*dir;
    }

    //沿着dir的方向走n步,然后反方向走一步
    inline int base_in(int n,int dir) {
        return base_ex(n,dir)-dir;
    }

    //前面第n个位置,不包括pos
    int pre_ex(int n) { return base_ex(n,-1);}
    //前面第n个位置,包括pos
    int pre_in(int n) { return base_in(n,-1);}

    //后面第n个位置,不包括pos
    int next_ex(int n) { return base_ex(n,1);}
    //后面第n个位置,包括pos
    int next_in(int n) { return base_in(n,1);}


};
