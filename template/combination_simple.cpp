//使用std::next_permutation的简单 组合 模板

#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>

const int maxn = 1e5;

using std::cin;
using std::cout;


// 从n个里选5个的所有可能性
int m =2;
int n =5;

// choose[i] = 0 对应的位置没有选
int choose[maxn];

void init() {
    cin >> n >> m;
}

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

//分隔用
void fence(int repeat=1) {
    for(int i = 1;i <= repeat ;++i ) // i: 1->repeat
    {
        pr("-------------------\n");
    }
}

//输出 choose数组
void print_choose() {
    std::cout << " choose : ";
    for(int i = 1;i <= n ;++i ) // i: 1->n
    {
        pr(choose[i]);
    }
    prln();
}


// 核心: 针对得到的choose数据时行数据的计算
void work() {
    // print_choose();
}

//n选m的所有可能
void combination(int n,int m) {

    std::vector<int> vec(n,0);
    // vec.resize(n);
    for(int i = vec.size() - m ;i<vec.size();++i)
        vec[i] = 1;

    do {
        memset(choose,0,sizeof(choose));
        for(int i = 0 ;i<vec.size();++i)
            choose[i+1] = vec[i];
        work();
    } while( std::next_permutation(vec.begin(),vec.end()) );
}



int main (int argc, char *argv[]) {
    init();
    combination(n,m);
    return 0;
}

