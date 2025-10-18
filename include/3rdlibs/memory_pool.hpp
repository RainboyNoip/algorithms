//@desc 内存池技术
/*
---- 文档---- 


*/

#include <cstddef>   // std::size_t, std::byte
#include <bit>       // std::countx_zeros c++20
#include <vector>
#include <cstring>
#include <stdlib.h>
#include <memory>
#include <assert.h>
#include <array>
#include <memory_resource>


namespace MEMORY_POOL {

//内存池中链表中的节点
//用于: 把申请的内存转换成PoolNode类型,然后进行操作
struct PoolNode {
    PoolNode * m_next;
};

//内存池
class Pool {

private:
    std::size_t m_block_size; // 一块的内存大小,申请内存的最小单元
    std::size_t m_block_per_chunk; // 一片内存有多少个块
    PoolNode * m_head; // 内存池链表表头
    std::array<void *,1024> m_chunks; // 记录 chunk(片内存)的头
public:

    Pool() noexcept :
        m_block_size(0),
        m_block_per_chunk(0),
        m_head(nullptr)
    {}

    Pool(std::size_t block_size,std::size_t block_per_chunk) noexcept;

    Pool(Pool && r);

    void swap(Pool &r);
    Pool & operator=(Pool && r);
    void initialize(std::size_t block_size, std::size_t block_per_chunk);

    void *alloc() noexcept;
    void free(void *node_) noexcept;
    ~Pool() noexcept;
};


//可以自删除,自添加的节点
struct FreeNode;


//stack
#include "memory_pool/stackFulPool.hpp"
#include "memory_pool/fixPoolRes.hpp"


}// namespace MEMORY_POOL 
