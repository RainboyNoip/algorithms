//一个不使用本代码库的模板,ver 0.1, upd at 2023-07-09
/* author: Rainboy email: rainboylvx@qq.com  time: 2023年 07月 09日 星期日 21:51:45 CST */
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1e6+5,maxe = 1e6+5; //点与边的数量

//////// 常用宏
#define F(n) for(int i=1;i<=n;++i)
#define FF(i,n) for(int i=1;i<=n;++i)
#define F3(i,s,n) for(int i=s;i<=n;++i)



/////////////// log,调试用
#define __LOG_INFO__   "[" << "Ln " << __LINE__  << "]: "

#ifndef DEBUG
#define log(...) std::cerr << __LOG_INFO__ ; __debug_with_arg_name(std::cerr,#__VA_ARGS__,__VA_ARGS__)
#else
#define log(...)
#endif

template<typename T1,typename... T2>
void __debug_with_arg_name(std::ostream & O , std::string_view args_str, T1&& arg1)
{

    O << args_str<< "=" << arg1 <<  '\n';
}

template<typename T1,typename... T2>
void __debug_with_arg_name(std::ostream & O , std::string_view args_str, T1&& arg1,T2&&... args) 
{
    auto p1 = args_str.find_first_of(",");
    O << args_str.substr(0,p1) << "=" << arg1  << ',';
    __debug_with_arg_name(O, args_str.substr(p1+1),std::forward<T2>(args)...);
}
///////////////////////

int n,m;
/* 定义全局变量 */

// int a[maxn]; //常用的一个数组 

void init()
{
    cin >> n >> m;
}

int main(int argc,char * argv[]){
    cin.sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    
    return 0;
}
