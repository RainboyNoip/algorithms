
/*


快速排序

https://www.colopen-blog.com/Algorithm/lydguid/z0x05_%E6%8E%92%E5%BA%8F/
*/

#ifndef __HEADER_BASE_HPP__
#include <algorithm>
#endif

//使用指针
// 核心思想: 当j停止的时候,j 的左边都是< key,右边都 >=key
template<typename T>
void quick_sort(T * l, T * r) {
    if( l >= r) return; //只有一个元素
    T * i = l-1;
    T * j = r+1;
    T  mid_pos = *(l + ((r - l) >>1)); //中间位置
    while( i < j) {
        do ++i ; while( *i < mid_pos);
        do --j ; while( *j > mid_pos);
        if( i < j) std::swap(*i,*j);
    }
    quick_sort(l, j);
    quick_sort(j+1,r);
}

//TODO
// 利用quick_sort, 求一个序列的第k大
template<typename T>
T quick_sort(T * l, T * r,int k);

//TODO
// 利用quick_sort, 求一个序列的第k小
template<typename T>
T quick_sort(T * l, T * r,int k);
