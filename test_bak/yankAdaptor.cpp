#include "utils/log.hpp"
#include "utils/type_name.hpp"

int a[100];
int b[10][10];

int main(){
    int x;
    int n = 10;
    _in >> YankArray(n)>> a;
    // _in >> Yank2DArray(5,5) >> b;
    // _out.println(a+1, a+1+10);
    a >> YankArray(n) >> _out;
    
    // for(int i=1;i<=5;++i){
    //     for(int j=1;j<=5;++j){
    //         _out.print(b[i][j]);
    //         _out.sp();
    //     }
    //     _out.ln();
    // }
    // b >> Yank2DArray(5,5) >> _out;


    return 0;
}

