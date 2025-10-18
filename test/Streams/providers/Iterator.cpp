#include "Streams/providers/providers.hpp"
#include "catch_amalgamated.hpp"
using namespace Stream;

TEST_CASE("Functional", "[lambda]") {
    int arr[] = {1,2,3,4};
    int arr_len = sizeof(arr) / sizeof(arr[0]);

    //创建一个Iterator 的provder 指针
    provider::Iterator<int,int *> myIter(arr,arr+arr_len);
    for(auto val : myIter) {
        std::cout <<val <<std::endl;
    }

    auto ptr = provider::make_stream_provider<provider::Iterator,int,int *>
            (arr,arr+arr_len);
    for(auto val : *ptr ) {
        std::cout <<val <<std::endl;
    }
}
