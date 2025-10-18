/**
 *
 * [C++ named requirements: Allocator - cppreference.com](https://en.cppreference.com/w/cpp/named_req/Allocator)
 * [std::allocator - cppreference.com](https://en.cppreference.com/w/cpp/memory/allocator)
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
#include <iostream>
#include <memory>
#include <cstdint> // uintptr_t

//自己实现的 std::align ,可以把下面的
//解释 https://lesleylai.info/en/std-align/
// 代码来自 bits/align.h
[[ nodiscard ]]
inline
void * myalign(std::size_t align,std::size_t bytes,
        void * & ptr,
        std::size_t & space
        )
{
    if( space < bytes) return nullptr;
    //转换成整数
    const auto intptr = reinterpret_cast<uintptr_t>(ptr);
    // algin是 2^x 那么 --> algined 就是align的整数倍
    const auto aligned = (intptr-1u+align) + ~(align-1);
    const auto diff = aligned - intptr; //差值
    if( diff + bytes > space)
        return nullptr;
    space -= diff;
    return ptr = reinterpret_cast<void*>(aligned);//修改ptr的值
}



//默认118MB
template<std::size_t _MemorySize = 118 >
struct mybuffer {
    // using value_type = T;
    // using pointer = value_type*;
    // using const_pointer = const value_type *;

    template<typename T>
    [[ nodiscard ]]
    T * allocate(std::size_t n,std::size_t __alignment = sizeof(T)) {
        auto __bytes = sizeof(T) * n;
        void* __p = std::align(__alignment, __bytes, _M_current_buf, _M_avail);

        if ( __p == nullptr) throw "allocate error";
        _M_current_buf = (char*)_M_current_buf + __bytes;
        _M_avail -= __bytes;
        return __p;
    }

    template<typename T>
    void delallocate(T * p,std::size_t n ) {
    }

    char memory_pool[_MemorySize*1024*1024];
    void * _M_current_buf = memory_pool;
    std::size_t _M_avail = 0;
};


template<typename T>
struct myAllocator {
    myAllocator() {

    }

};
