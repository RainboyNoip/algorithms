#include "base.hpp"
#include "algo/quick_sort.hpp"

//排序测试

int n;
int a[maxn];
int main(){
    in >> n;
    in >> YankArray(n) >> a;
    
    // quick_sort(a+1, a+n);
    std::sort(a+1,a+1+n);
    a >> YankArray(n) >> out; //输出
    return 0;
}
