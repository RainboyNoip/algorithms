//大衍求一术
// TODO 补充完整口诀
#include "math/common.hpp"


// 置衍右上,定居下,立天元一于左上
//
// 对应位置
// 0 1 -> 00 01
// 2 3    10 11


long long great_infernce(int a,int n) {
    using ll = long long ;
    ll t[4] = {1,a,0,n}; // 置衍右上,定居下,立天元一于左上

    // 先以右上除以右下,所得商数与左上一相乘并入左下

    while( t[1] != 1)
    {
        int divor = t[1] < t[3] ? 1 : 3; // 得到较小的那个数,也就是除数
        int dived = divor ^ 0b10; //得到被除数,也就是较大的那个数
        ll q = t[dived] / t[divor]; // 商, quotient
        t[dived] %= t[divor];
        t[dived ^ 1] += t[dived^0b11] *q;// 商相乘对角的左,并入左下(平行的左)
        // std::cout << t[0] << " " << t[1] << std::endl;
        // std::cout << t[2] << " " << t[3] << std::endl;
        // std::cout << "------------\n";
    }

    return t[0];
}
