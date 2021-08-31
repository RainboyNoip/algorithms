#include <algorithm>

#include <algo/random.hpp>
#include <algo/algorithms/binary_search.hpp>

#include "tinytest.h"


void test_binary_search (){
    using namespace rainboy;
    Random rnd;
    int a[10];
    for(int i=0;i<=9;++i){
        a[i] = rnd(1,20);
    }
    std::sort(a, a+10+1);

    //for(int i=0;i<=9;++i) std::cout << a[i] << " ";
    //std::cout  << std::endl;

    auto it = bs(a,a+9+1,a[5]);
    //std::cout << a[5] << std::endl;
    //std::cout << (it - a) << std::endl ;
    auto idx = a+0;
    for(int i=0;i<=10;++i) //找到第一个不符合 默认条件的数
        if( i == 10 or not std::less<int>{}(a[i],a[5])) {
            idx = a+i;break;
        }
    ASSERT_EQUALS(idx,it);

    auto it2 = bs(a,a+9+1,a[5],std::less_equal<int> ());
    for(int i=0;i<=10;++i) //找到第一个不符合 默认条件的数
        if( i == 10 or not std::less_equal<int>{}(a[i],a[5])) {
            idx = a+i;break;
        }

    ASSERT_EQUALS(idx,it2);


}
