/* ====================================================
 * 可以给 stl容器使用的 分配器
 *  特点，预先分配空间
 * */

#pragma once
#include <cstddef>  //for size_t
#include <array>
#include <iterator>

namespace algo {

// 根据 [std::allocator - cppreference.com](https://en.cppreference.com/w/cpp/memory/allocator) 描述
/*
 *Member types
 *      value_type	T
 *      pointer (deprecated in C++17)(removed in C++20)	T*
 *      const_pointer (deprecated in C++17)(removed in C++20)	const T*
 *      reference (deprecated in C++17)(removed in C++20)	T&
 *      const_reference (deprecated in C++17)(removed in C++20)	const T&
 *      size_type	std::size_t
 *      difference_type	std::ptrdiff_t
 *      propagate_on_container_move_assignment(C++14)	std::true_type
 *      rebind 	template< class U > struct rebind {
 *          typedef allocator<U> other;
 *      };
 *      is_always_equal(C++17)(deprecated in C++20)	std::true_type
 *
    (constructor)
    (destructor)
    address obtains the address of an object, even if operator& is overloaded
    allocate
    allocate_at_least (C++23)
    construct constructs an object in allocated storage
    destroy destructs an object in allocated storage
    Non-member functions
        operator==
        operator!= compares two allocator instances
 */

//Idea 超过128 就单独挂载到一个大块 free_list 上
template<typename T,size_t _Size=1000000 /* 1e6 */  >
struct allocator {

public:
    using value_type      = T;
    using pointer         = T*;
    using const_pointer   = const T *;
    using reference       = T&;
    using const_reference = const T&;
    using size_type       = std::size_t;
    using difference_type = std::ptrdiff_t;

    template<typename U>
    struct rebind { using other = allocator<T, _Size>;};

    allocator() : _M_mem_begin{std::begin(_M_mem)},_M_mem_end{std::end(_M_mem)}
        {};

    union obj {
        union obj * free_list_link;
        char client_data[1];
    };
    enum { __ALIGN = 8};
    enum { __MAX_BYTES= 8};

        void
    mem_pool(){
    }

    // n个大小为sizeof(T) 的连续空间
    pointer allocate( size_type n, const void * hint = 0 ) {
        auto tmp = _M_mem_begin;
        _M_mem_begin += n;
        return static_cast<pointer>(tmp);
    }

private:
    using _S_Mem__T = std::array<T, _Size>;
    using _Iterator = decltype(std::begin(std::declval<_S_Mem__T>()));
    using difference_type_mem = typename std::iterator_traits<_Iterator>::difference_type;
    _S_Mem__T           _M_mem;
    _Iterator           _M_mem_begin;
    _Iterator           _M_mem_end;
    difference_type_mem _M_mem_size;

}; // struct allocator

} // namespace algo
