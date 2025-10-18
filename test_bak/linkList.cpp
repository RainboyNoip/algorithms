//一个测试linkList 是否能用的程序

#include "graph/linkList.hpp"
using namespace std;

/*
        _____1______
       /            \
    __2__          __3__
   /     \        /     \
  4       5      6       7
*/

//定义一个树
int tree[][2] = {
    1,2,
    1,3,
    2,4,
    2,5,
    3,6,
    3,7
};

graph_nw tree1;

void dfs(int u,int parent) {

    cout << u << " ";
    for(auto v : tree1.start_from_head(u))
    {
        if ( v == parent) continue;
        dfs(v,u);
    }
}
int main () {
    for(int i = 0 ;i< sizeof(tree)/sizeof(tree[0][0])/2 ;i++ )
    {
        int u = tree[i][0];
        int v = tree[i][1];
        tree1.add(u,v);
    }
    cout << tree1.size() << std::endl;
    dfs(1,0);

    return 0;
}
