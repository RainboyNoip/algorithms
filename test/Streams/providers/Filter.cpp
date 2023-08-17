#include "Streams/providers/providers.hpp"
#include "catch_amalgamated.hpp"
using namespace Stream;

TEST_CASE("Functional", "[lambda]") {
    int arr[] = {1,2,3,4,6,7,8,9,10};
    int arr_len = sizeof(arr) / sizeof(arr[0]);

    //创建一个Iterator 的provder 指针
    auto IterPtr = provider::make_stream_provider<provider::Iterator,int,int *>
            (arr,arr+arr_len);

    auto filter = provider::filter(std::move(IterPtr),[](int &a ) { return a % 2 == 0;});

    //输出过滤后的数值: 偶数
    for(auto val : filter) {
        std::cout << val << std::endl;
    }
}
