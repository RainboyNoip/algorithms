#define maxn 1000005
#define maxe 2000005
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

using std::cin;
using std::cout;

//////// 常用宏
#define F(n) for(int i=1;i<=n;++i)
#define FF(i,n) for(int i=1;i<=n;++i)
#define F3(i,s,n) for(int i=s;i<=n;++i)

#ifdef DEBUG
#include "utils/clock.hpp"
#include "utils/log.hpp"
#else
#define log(...)
#endif


int n,m;
/* 定义全局变量 */

// int a[maxn]; //常用的一个数组 

void init()
{
    cin >> n >> m;
}

int main(){
    cin.sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
#ifdef DEBUG
    Clock __time_calc__("main time");
#endif
    init();
    return 0;
}
