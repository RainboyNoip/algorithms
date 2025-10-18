//用exgcd 求二元一次不定方程的一个解 a*x + b*y = (a,b)
// 记忆要点
//(a,b) => (b,r1)
// x,y      nx,ny
// 能推导出x,y与nx,ny之间的关系

int exgcd(int a,int b,int & x,int &y) {
    if( a < b ) 
        std::swap(a,b);
    if( a % b == 0) { //此时的最大公约数就是b
        x = 0;
        y = 1;
        return b;
    }
    int nx,ny;

    int gcd = exgcd(b,a%b,nx,ny);
    y = nx-ny * (a/b);
    x = ny;
    return gcd;
}
