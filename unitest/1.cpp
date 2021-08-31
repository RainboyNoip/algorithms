#include <cstdio>
#include <iostream>
#include "./linked_forward_start.hpp"
using namespace std;

struct node {
    void get_address(){
        cout << this << endl;
    }
};
node a[100];

linkedForwardStar lfs;

int main(){
    int n,m;
    scanf("%d",&m);
    for(int i=1;i<=m;++i){
        int u,v;
        scanf("%d%d",&u,&v);
        lfs.add(u, v);
    }
    //auto t = lfs[2];
    for (const auto& e : lfs[1]) {
        cout << e << endl;
    }
    return 0;
}
