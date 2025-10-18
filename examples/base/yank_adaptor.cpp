#include "base/yank_adaptor.hpp"

int a[10];

struct node {
    int u,v;
};

node b[10];

//修改默认的行为
void operator>>(fast_in & in , node & n ) {
    in.read(n.u,n.v);
}

//修改默认的行为
void operator<<(fast_out & out , node & n ) {
    // in.read(n.u,n.v);
    out.println(n.u,n.v);
}

int main(){
    int n = 5;
    //写入一维数组
    in >> __YankArray(n) >> a;
    out.print(a,a+n);
    out.ln();

    //写入一维结构体数组
    in >> __YankArray(n) >> b;
    //一维结构体数组输出
    b >> __YankArray(n) >> out;
    return 0;
}
