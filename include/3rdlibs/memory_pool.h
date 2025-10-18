#ifndef TINYASYNC_MEMORY_POOL_H
#define TINYASYNC_MEMORY_POOL_H

#include <cstddef>   // std::size_t, std::byte
#include <bit>       // std::countx_zeros
#include <vector>
#include <cstring>
#include <stdlib.h>
#include <memory>
#include <assert.h>

// #if defined(__clang__)
//
// #include <experimental/memory_resource>
// namespace std {
//     namespace pmr {
//         using std::experimental::pmr::memory_resource;
//         using std::experimental::pmr::get_default_resource;
//         using std::experimental::pmr::set_default_resource;
//         using std::experimental::pmr::new_delete_resource;
//     }
// }
// #else

#include <memory_resource>

// #endif

namespace tinyasync
{

    struct PoolNode {
        PoolNode *m_next;
    };

    class Pool
    {

    public:
        Pool() noexcept : m_block_size(0), m_block_per_chunk(0), m_head(nullptr)
        {
        }

        Pool(std::size_t block_size, std::size_t block_per_chunk) noexcept
        {
            initialize(block_size, block_per_chunk);
        }

        Pool(Pool &&r)
        {
            m_block_size = r.m_block_size;
            m_block_per_chunk = r.m_block_per_chunk;
            m_head = r.m_head;
            m_chunks = std::move(r.m_chunks);
            r.m_head = nullptr;
            r.m_block_size = 0;
            r.m_block_per_chunk = 0;
        }

        void swap(Pool &r)
        {
            std::swap(m_block_size, r.m_block_size);
            std::swap(m_block_per_chunk, r.m_block_per_chunk);
            std::swap(m_head, r.m_head);
            std::swap(m_chunks, r.m_chunks);
        }

        Pool &operator=(Pool &&r)
        {
            Pool pool(std::move(r));
            return *this;
        }

        void initialize(std::size_t block_size, std::size_t block_per_chunk)
        {
            m_block_size = std::max(sizeof(void *), block_size);
            m_block_per_chunk = block_per_chunk;
            m_head = nullptr;
        }

        size_t m_block_size;
        size_t m_block_per_chunk;
        PoolNode *m_head;

        std::vector<void *> m_chunks; //记录一系列指针

        void *alloc() noexcept
        {
            auto head = m_head;
            if (!head) {
                    auto block_per_chunk = m_block_per_chunk;
                    auto block_size = m_block_size;
                    std::size_t memsize = block_size * block_per_chunk;
                    if (!memsize)
                    {
                        return nullptr;
                    }
                    // max alignment
                    auto *h = ::malloc(memsize);
                    if (!h)
                    {
                        return h;
                    }
                    m_chunks.push_back(h);
                    for (std::size_t i = 0; i < block_per_chunk - 1; ++i)
                    {
                        PoolNode *p = (PoolNode *)(((char *)h) + block_size * i);
                        PoolNode *p2 = (PoolNode *)(((char *)h) + block_size * (i + 1));
                        p->m_next = p2;
                    }
                    PoolNode *p = (PoolNode *)(((char *)h) + block_size * (block_per_chunk - 1));
                    p->m_next = nullptr;
                    m_head = (PoolNode *)h;
                    head = m_head;
            }
            m_head = head->m_next;
            return head;
        }

        void free(void *node_) noexcept
        {
            auto node = (PoolNode *)node_;
            node->m_next = m_head;
            m_head = node;
        }

        ~Pool() noexcept
        {
            for (auto *p : m_chunks)
            {
                ::free(p);
            }
        }
    };

    struct FreeNode
    {
        FreeNode *m_next;
        FreeNode *m_prev;

        void init()
        {
            m_next = this;
            m_prev = this;
        }

        bool remove_self()
        {
            auto prev = this->m_prev;
            auto next = this->m_next;
            next->m_prev = prev;
            prev->m_next = next;
            return prev == next;
        }

        void push(FreeNode *node)
        {
            auto next = m_next;
            node->m_next = next;
            node->m_prev = this;
            this->m_next = node;
            next->m_prev = node;
        }
    };

    struct PoolBlock
    {
        static const uint32_t k_free_mask = 1<<7; // 1000 0000
        static const uint32_t k_order_mask = 0x7F; // 0111 1111

        uint32_t m_prev_size;
        // 低8位的表示:
        // 其它表示: 真正的大小
        uint32_t m_size;      // total size include header
        FreeNode m_free_node; //一个freeNode结点,使PoolBlock可以连接上FreeNode链表上

        uint32_t prev_size() { // 前一个block的大小
            return m_prev_size >> 8; // 除 2^8
        }

        uint32_t prev_free() {
            return m_prev_size & k_free_mask;
        }

        std::size_t prev_order() { // 前一个block的 order
            return m_prev_size & k_order_mask;
        }

        static uint32_t encode_size(uint32_t size, std::size_t order, bool free) {
            return (size<<8) | order | (free?k_free_mask:0);
        }

        uint32_t size() {
            return m_size >> 8;
        }

        uint32_t free_() { // 是否是free的,
            return m_size & k_free_mask;
        }

        std::size_t order() {
            return m_size & k_order_mask;
        }

        void *mem() // 内存的地址
        {
            return (char *)this + 2*sizeof(uint32_t); // 略过,m_prev_size,m_size
        }

        //这个是上面的 mem 的逆函数
        static PoolBlock *from_mem(void *p) //从一个内存块转成PoolBlock
        {
            assert((void *)p > (void *)100);
            return (PoolBlock *)((char *)p - 2*sizeof(uint32_t));
        }

        //从一个FreeNode转成PoolBlock
        static PoolBlock *from_free_node(FreeNode *node)
        {
            assert(node > (void *)100);
            return (PoolBlock *)((char *)node - offsetof(PoolBlock, m_free_node));
        }
    };

    // inline std::map<void *, bool> m_allocated;

    struct PoolImpl
    {
        static const int k_max_order = 48;
        static const int k_malloc_order = 44;

        uint64_t m_free_flags; // m_free对应位置是否有free的Node
        FreeNode m_free[k_max_order + 1];

        FreeNode m_chuncks;

        PoolImpl()
        {
            for (auto &m : m_free) //初始化每个FreeNode
            {
                m.m_next = &m;
                m.m_prev = &m;
            }
            m_free_flags = 0;
            m_chuncks.init(); // 指向自己的freeNode
        }

        ~PoolImpl() //析构
        {            
            for(auto i = 0; i < k_max_order; ++i) {
                assert(m_free[i].m_next == &m_free[i]);
            }

            auto c = m_chuncks.m_next;
            for(;c != &m_chuncks;) {
                auto next = c->m_next;
                auto p = PoolBlock::from_free_node(c);
                ::free(p);
                c = next;
            }
        }

        static constexpr uint16_t s1(std::size_t s) {
            return s + s/4;
        }
        static constexpr uint16_t s2(std::size_t s) {
            return s + s/2;
        }
        static constexpr uint16_t s3(std::size_t s) {
            return s + 3*s/4;
        }

        //根据传入的大小 返回它在table所在的位置
        //例如 8->0  9->1 10->1 11->2
        // 整个table中记录的尺寸如下
        //8 10 12 14 16 20 24 28 32 40 48 56 64 80 96 112 128 160 192 224 256 320 384 448 512 640 768 896 1024 1280 1536 1792 2048 2560 3072 3584 4096 5120 6144 7168 8192 10240 12288 14336 16384 20480 24576 28672 32768
        static uint16_t block_order(std::size_t block_size)
        {
#if 0
            static constexpr uint16_t table[] = {
                                    8, s1(8), s2(8), s3(8),
                                    16, s1(16), s2(16), s3(16),
                                    32, s1(32), s2(32), s3(32),
                                    64, s1(64), s2(64), s3(64),
                                    128, s1(128), s2(128), s3(128),
                                    256, s1(256), s2(256), s3(256),
                                    512, s1(512), s2(512), s3(512),
                                    1<<10, s1(1<<10), s2(1<<10), s3(1<<10),
                                    1<<11, s1(1<<11), s2(1<<11), s3(1<<11),
                                    1<<12, s1(1<<12), s2(1<<12), s3(1<<12),
                                    1<<13, s1(1<<13), s2(1<<13), s3(1<<13),
                                    1<<14, s1(1<<14), s2(1<<14), s3(1<<14),
                                    1<<15, 
                                    };

            auto end = table + sizeof(table)/sizeof(table[0]);
            auto p = std::lower_bound(table, end, block_size);
            assert(p != end);
            return p - table;
#else
            const size_t block_size_ = block_size;
            const size_t shift = sizeof(block_size_)*8 - std::countl_zero(block_size_) - 3;
            const size_t block_size__ = block_size_ >> shift;
            const size_t block_size_2 = block_size__ & 3;
            const size_t block_size_3 = (shift-1)*4 + block_size_2;
            const size_t order = block_size_3 + bool(block_size_ & ((1<<shift)-1) );
            return order;
#endif
        }

        static std::size_t block_size(std::size_t block_order)
        {
            static constexpr uint16_t table[] = {
                                    8, s1(8), s2(8), s3(8),
                                    16, s1(16), s2(16), s3(16),
                                    32, s1(32), s2(32), s3(32),
                                    64, s1(64), s2(64), s3(64),
                                    128, s1(128), s2(128), s3(128),
                                    256, s1(256), s2(256), s3(256),
                                    512, s1(512), s2(512), s3(512),
                                    1<<10, s1(1<<10), s2(1<<10), s3(1<<10),
                                    1<<11, s1(1<<11), s2(1<<11), s3(1<<11),
                                    1<<12, s1(1<<12), s2(1<<12), s3(1<<12),
                                    1<<13, s1(1<<13), s2(1<<13), s3(1<<13),
                                    1<<14, s1(1<<14), s2(1<<14), s3(1<<14),
                                    1<<15, 
                                    };
            return table[block_order];
        }

        //右边0的个数
        static std::size_t ffs64(uint64_t v)
        {
            return std::countr_zero(v);
        }

        //对应的order 添加 新的内存
        void add_free_block(PoolBlock *block, std::size_t order)
        {
            std::size_t idx = order;
            m_free[idx].push(&(block->m_free_node));
            m_free_flags |= (uint64_t(1) << idx); // m_free对应的下标有内容
        }

        // Block在PoolImpl上自我清除,然后设置对应的标志
        void remove_free_block(PoolBlock *block, std::size_t order)
        {
            if (block->m_free_node.remove_self())
            {
                std::size_t idx = order;
                m_free_flags &= ~(uint64_t(1) << idx); //对应的位置删空了,就置空标记
            }
        }

        // * block 指针
        // * block_size,当前block应该有的大小
        // align 对齐,当前block应该的对齐
        PoolBlock *break_(PoolBlock *block, std::size_t const block_size, std::size_t align)
        {

            auto old_size = block->size(); //原来block的大小
            assert(block_size <= old_size); // block_size 要比较原始大小 小

            //使用面做为 新的block
            void *ptr = (char*)block + old_size - block_size + 2*sizeof(uint32_t);
            // + 2*sizeof(uint32_t) 因为 参数 block_size 已经包含 2个 uint32_t 的大小了

            //向前移动一点,保证对齐
            void *ptr_align = (void*)((std::ptrdiff_t)ptr & ~(align-1));

            //对齐后 再留两个 uint32_t(m_prev_size,m_size)
            PoolBlock* block2 = (PoolBlock*)((char*)ptr_align - 2*sizeof(uint32_t));
            // 保证block2->mem() 一定是对齐的

            //中间的差值
            std::size_t new_size = (char*)block2 - (char*)block;


            //差值比 一个 PoolBlock 小
            if (new_size < sizeof(PoolBlock))
            {
                // use whole block
                remove_free_block(block, block->order());

                auto block_next = next_block(block, old_size); //这一句没有用啊
                auto encode_size = block->m_size & ~PoolBlock::k_free_mask;
                block->m_size = encode_size;
                block_next->m_prev_size =  encode_size;
                return block;
            } else  { // 差值比一个 PoolBlock 大
                change_block_size(this, block, new_size, block2); // 分割大小

                auto block2_size = old_size - new_size;
                assert(block2_size >= block_size); //

                auto block2_next = next_block(block2, block2_size); // 这个block2_next有什么用 ?
                auto new_ord = block_order(block2_size);
                auto encode_size = PoolBlock::encode_size(block2_size, new_ord, false);
                block2->m_size = encode_size;
                block2_next->m_prev_size = encode_size;

                return block2;
            }
        }

        // 申请内存
        // size 申请内存的大小
        // alignof 对齐
        static void *alloc(PoolImpl *pool, std::size_t size, std::size_t align = alignof(std::max_align_t))
        {
#if __USE_ASYNC_UTILS__
            printf("in PoolImpl alloc ,size = %lld, \n",size);
#endif


            //至少要存下两个指针的大小
            std::size_t size_ = std::max(size, 2*sizeof(void*)); // 至少是16
            align = std::max(2*sizeof(uint32_t), align); // 对齐至少是 8

            // size_ + 2个uint32_t( m_prev_size,m_size) ,一个block的区间
            const std::size_t block_size = 2*sizeof(uint32_t) + size_; // 要申请大小,要有两个uint32_t,组成的block_size

            //为什么要加 align ???
            const std::size_t block_size_ = size_ + align; 
            //要申请的大小2,考虑到最大的align的可能
            
            if (block_size_ >= PoolImpl::block_size(k_malloc_order)) //大于最大的尺寸16384byte
            {
                return ::aligned_alloc(align, size); // 由系统申请
            }


            //             v--- allocated block
            //             [prev_size size][          size_         ]
            //             [           block_size                   ]
            // [    align                 ]
            // [              block_size_                           ]

            auto idx_ = PoolImpl::block_order(block_size_); //得到应该用那个尺寸

            std::size_t idx;
            PoolBlock *block;

            // ffs64这里作用, 找右边有几个0
            // 如果返回值不是64,就代表 m_free_flags 从右边数有一个位置(代表m_free对应位置的下标)
            // 有一个链表不空,且这块内存>= 需要的内存
            //
            // pool->m_free_flags & ~((uint64_t(1) << idx_) - 1)
            //  把m_free_flags idx位置右边的都清空
            idx = ffs64(pool->m_free_flags & ~((uint64_t(1) << idx_) - 1)); 

            if (idx != 64) // 找能用的最小的地方
            {
                FreeNode &node = pool->m_free[idx];
                auto next = node.m_next;
                if (next == &node)
                {
                    // empty
                    assert(next != &node); // ???? 空了就会错
                }
                block = PoolBlock::from_free_node(next);
            }
            else // idx右边有64个0,m_free全部为空,申请新的内存
            {
                auto size = PoolImpl::block_size(k_max_order); // 直接申请最大的内存块,32kb
                auto head = (PoolBlock *)::malloc(size + 2*sizeof(PoolBlock));// 系统申请内存,sizeof(PoolBlock)=24
                // auto tail = (PoolBlock *)((char*)head + size); // ?? 为什么是+size
                auto tail = (PoolBlock *)((char*)head + size + sizeof(PoolBlock) ); // 改成末尾,by rainboy
                block = (PoolBlock *)(head + 1); // block
                // auto tail = block + size;

                block->m_prev_size = PoolBlock::encode_size(0, 0, false); // 前一个 : 大小0, order,0,free=false
                block->m_size = PoolBlock::encode_size(size, k_max_order, true); //当前,大小,size,order,free=true

                tail->m_size = PoolBlock::encode_size(0, 0, false);

                pool->m_chuncks.push(&head->m_free_node); //记录申请的内存,free的时候用
                pool->add_free_block(block, k_max_order);
            }

            //break_: 将一个大块的内存,拆成小块
            block = pool->break_(block, block_size, align);

            assert(!block->free_());
            return block->mem(); //得到地址
        }

        //Block 跨过 size大小后的下一个Block
        static PoolBlock *next_block(PoolBlock* block, std::size_t size) {
            return (PoolBlock*)((char*)block + size);
        }

        static PoolBlock *prev_block(PoolBlock* block, std::size_t size) {
            return (PoolBlock*)((char*)block - size);
        }

        // 将 block 改成 new_size大小
        // new_size 新的大小
        // next 下一个block
        static void change_block_size(PoolImpl *pool, PoolBlock *block, std::size_t new_size, PoolBlock *next)
        {
            auto old_ord = block->order(); //原来的大小
            std::size_t order = block_order(new_size);  // 新的order
            uint32_t encode_size = PoolBlock::encode_size(new_size, order, true);
            block->m_size = encode_size;
            next->m_prev_size = encode_size;

            if (old_ord != order) // 不是原来的order
            {
                pool->remove_free_block(block, old_ord); // 去除
                pool->add_free_block(block, order); // 添加
            }
        }

        static void change_block_size(PoolImpl *pool, PoolBlock *block, std::size_t new_size, PoolBlock *next,
            PoolBlock *new_block)
        {
            auto old_ord = block->order();
            std::size_t order = block_order(new_size);
            uint32_t encode_size = PoolBlock::encode_size(new_size, order, true);
            new_block->m_size = encode_size;
            next->m_prev_size = encode_size;

            pool->remove_free_block(block, old_ord);
            pool->add_free_block(new_block, order);
        }

        //释放内存
        // pool 哪个内存池, p 释放内存的指针 size 大小, align 对齐
        static void free(PoolImpl *pool, void *p, std::size_t size, std::size_t align)
        {

#if __USE_ASYNC_UTILS__
            printf("in PoolImpl free ,size = %lld, \n",size);
#endif
            std::size_t size_ = std::max(size, 2*sizeof(void*)); // 内存至少16tybe
            align = std::max(2*sizeof(uint32_t), align); // 对齐至少是8
            const std::size_t block_size_ = size_ + align;// 推算出块的大小 size_ + align
            if (block_size_ >= block_size(k_malloc_order)) // 大于指定的最大内存
            {
                ::free(p); // 由系统释放
                return;
            }
            
            PoolBlock *cur = PoolBlock::from_mem(p); // 从内存转成 PoolBlock
            auto cur_free = cur->free_();
            assert(!cur_free); // 这块内存必须是 no free, 也就是被使用的,而不是在内存池中

            auto cur_size = cur->size(); // 当前内存块的大小
            auto prev_free = cur->prev_free(); // 前一块内存是否free

            PoolBlock *next = next_block(cur, cur_size);
            auto next_free = next->free_();

            // 前后的内存都是free的,也就是都在内存池中
            if (prev_free && next_free) 
            {
                auto next_size = next->size();
                auto prev_size = cur->prev_size();
                
                auto size = prev_size + cur_size + next_size;
                auto prev = prev_block(cur, prev_size);

                pool->remove_free_block(next, next->order());

                auto nn = next_block(next, next_size);
                //把这些内存拼接在一起,重新放入内存池中?
                change_block_size(pool, prev, size, nn); 
            }
            else if (prev_free) // 只有前面是free的,只和前面拼接
            {
                auto prev_size = cur->prev_size();

                auto size = prev_size + cur_size;
                auto prev = prev_block(cur, prev_size);

                change_block_size(pool, prev, size, next);
            }
            else if (next_free) //只和后面拼接
            {
                auto next_size = next->size();
                auto size = cur_size + next_size;

                auto nn = next_block(next, next_size);
                change_block_size(pool, next, size, nn, cur);       
            }
            else //单独加入内存池中
            {
                auto order = cur->order();
                uint32_t encode_size = cur->m_size | PoolBlock::k_free_mask;

                next->m_prev_size = encode_size;
                cur->m_size = encode_size;
                pool->add_free_block(cur, order);
            }
        }
    };

    // 给StackfulPool构造用
    struct StackfulPoolArg {
        char *m_base;
        char *m_guard;       
    };
    
    //一种栈类型的内存池,申请内存后按FILO的顺序dealloc内存
    struct StackfulPool
    {
        char *m_base; // ?
        char *m_guard;// ?

        template<class T>
        struct StackfulAllocator //申请器
        {
            using value_type = T;

            template<class U>
            StackfulAllocator(StackfulAllocator<U> r) {
                m_pool = r.m_pool;
            }

            StackfulAllocator() {
                m_pool = nullptr;
            }

            StackfulPool *m_pool; // 指针

            //申请 sz 个 T 元素大小的内存
            void *allocate(std::size_t sz) {
                return m_pool->allocate(sz * sizeof(T), alignof(T));
            }
            void deallocate(void *p, std::size_t sz) {
                m_pool->deallocate(p, sz * sizeof(T), alignof(T));
            }
        };

        auto get_allocator_for_task() { //字节大小的申请器
            StackfulAllocator<std::byte> alloc;
            alloc.m_pool = this;
            return alloc;
        }
        
        // 申请内存作用内存池
        StackfulPool(std::size_t sz) {
            sz = up_round(sz, alignof(std::max_align_t));
            m_guard = (char*)::malloc(sz);
            m_base = m_guard + sz;
        }

        StackfulPoolArg as_arg() {
            StackfulPoolArg arg;
            arg.m_base = this->m_base;
            arg.m_guard = this->m_guard;
            return arg;            
        }

        StackfulPool(StackfulPoolArg arg) {
            m_base = arg.m_base;
            m_guard = arg.m_guard;
        }

        ~StackfulPool() {
            ::free(m_guard);
        }

        [[noreturn]]
        static void throw_exception()
        {
            throw std::bad_alloc();
        }

        /* @brief Rounds up the given size to the nearest multiple of alignment.*/
        static std::size_t up_round(std::size_t sz, std::size_t align) {
            return (sz + align - 1) & ~(align-1);
        }

        //申请 bytes 大小的内存,以alignment 对齐
        void* allocate(size_t bytes, size_t alignment = alignof(std::max_align_t))
        {

            // Check if the requested alignment exceeds the maximum alignment
            if(alignment > alignof(std::max_align_t)) {
                auto base = m_base;
                base -= bytes;
                // Align the base pointer based on the requested alignment
                base = (char*)(std::uintptr_t(base) & ~(alignment-1));
                
                if(base < m_guard) {
                    throw_exception();
                }

                auto bytes1 = up_round(bytes, sizeof(std::size_t));
                auto bytes2 = up_round(bytes, alignment);
                if(bytes1 == bytes2) { // 这里代码暗示我,只有在这种情下,才可能出现内存不中的情况
                    auto size = m_base - base;
                    if(size < sizeof(std::size_t)) { // not enough space to fit std::size_t
                        base -= alignment;
                    }
                }
                auto pbase = (char**)((char*)base + bytes1);
                *pbase = m_base; // record original m_base for dealloc

                m_base = base;
                return base;

            } 
            // Perform a simpler alignment process for alignment <= alignof(std::max_align_t)
            else {
                // bytes = (bytes + alignof(std::max_align_t) - 1) & ~(alignof(std::max_align_t)-1);
                bytes = up_round(bytes, alignof(std::max_align_t));
                auto base = m_base;
                base -= bytes;
                
                if(base < m_guard) {
                    throw_exception();
                }

                m_base = base;
                return base;
            }
        }

        void deallocate(void* p, size_t bytes, size_t alignment = alignof(std::max_align_t))
        {
            if(alignment > alignof(std::max_align_t)) {
                auto bytes1 = up_round(bytes, sizeof(std::size_t));
                m_base = *(char**)((char*)p + bytes1);
            } else {
                bytes = (bytes + alignof(std::max_align_t) - 1) & ~(alignof(std::max_align_t)-1);
                m_base = (char*)p + bytes;
            }
        }
    };

    // 每内申请内存大小固定
    class FixPoolResource : public std::pmr::memory_resource
    {
        Pool m_impl;
    public:

        FixPoolResource(size_t block_size) {
            m_impl.initialize(block_size, 100);
        }
        FixPoolResource(FixPoolResource&&) = delete;
        FixPoolResource &operator=(FixPoolResource&&) = delete;

        virtual void *
        do_allocate(size_t __bytes, size_t __alignment) override
        {
            return m_impl.alloc();
        }

        virtual void
        do_deallocate(void *__p, size_t __bytes, size_t __alignment) override
        {
            m_impl.free(__p);
        }

        virtual bool
        do_is_equal(const std::pmr::memory_resource &__other)  const noexcept override
        {
            return this == &__other;
        }
    };

    // 基于表的内存池
    class PoolResource : public std::pmr::memory_resource
    {
        PoolImpl m_impl;
    public:

        PoolResource() = default;
        PoolResource(PoolResource&&) = delete;
        PoolResource &operator=(PoolResource&&) = delete;

        virtual void *
        do_allocate(size_t __bytes, size_t __alignment) override
        {
            return PoolImpl::alloc(&m_impl, __bytes, __alignment);
        }

        virtual void
        do_deallocate(void *__p, size_t __bytes, size_t __alignment) override
        {
            PoolImpl::free(&m_impl, __p, __bytes, __alignment);
        }

        virtual bool
        do_is_equal(const std::pmr::memory_resource &__other)  const noexcept override
        {
            return this == &__other;
        }
    };

    // 一个自用的的buffer 容器
    template<typename T = std::byte>
    class vector_buffer {

        std::pmr::polymorphic_allocator<T> m_poly_alloc; //申请器
        std::size_t m_tot_size; //总内存的容量
        std::size_t m_size;     //已经使用的大小
        T * buff = nullptr;       //内存的的起始地址

    public:
        
        vector_buffer(std::size_t base_size,std::pmr::memory_resource * pmr_res)
            : m_poly_alloc(pmr_res),
            m_size{0}, m_tot_size{base_size}
        {
            buff = m_poly_alloc.allocate(base_size);
        }

        //得到起始 buff
        T * get_raw_buff() const { return buff;}
        T * get_write_buff() { return buff + m_size;}

        std::size_t get_tot_size() const  { return  m_tot_size;}
        std::size_t get_write_size() const  { return  m_tot_size - m_size;}

        void update_use_size(std::size_t use_size) {
            m_size += use_size;
        }

        //拓展更大的内存
        void expand(){
            auto new_tot_size = m_tot_size * 2;
            T * new_buff = m_poly_alloc.allocate(new_tot_size);


            if( buff) {
                std::memcpy(new_buff,buff,sizeof(T) * m_tot_size );
                m_poly_alloc.deallocate(buff,m_tot_size);
            }
            m_tot_size = new_tot_size;
            buff = new_buff;
        }


        ~vector_buffer(){
            if( buff)
                m_poly_alloc.deallocate(buff,m_tot_size);
        }

    };
} // namespace tinyasync

#endif

