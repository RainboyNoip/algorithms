//@desc 基于c++17 memory_resource


#include "base.hpp"

#ifndef __MEMORY_POOL_HPP
#define  __MEMORY_POOL_HPP

namespace rainboy {

    // return size*1024*1024;
    constexpr std::size_t operator ""_mb(unsigned long long size) { return (size << 20) ; }

    //内存池
    class memoryPool : public std::pmr::memory_resource
    {
        private:
            std::pmr::memory_resource* upstream;  // wrapped memory resource
            std::size_t total{0}; //统计总共申请的内存容量
        public:
            // we wrap the passed or default resource:
            explicit memoryPool(std::pmr::memory_resource* us
                    = std::pmr::get_default_resource())
                : upstream{us} 
            {}

            ~memoryPool() override {
                std::cerr << "Total use memory size : " ;
                if( total > 1024 *1024)
                    std::cerr<< std::setprecision(2) << (total/ 1024.0 /1024.0) << " mb";
                else if( total > 1024)
                    std::cerr << std::setprecision(2) << total / 1024.0 << " kb";
                else
                    std::cerr << total << " bytes";
                std::cerr << "\n";
            }

        private:
            void* do_allocate(std::size_t bytes, size_t alignment) override {
#if defined (RAINBOY_DEBUG) && defined (MEMORY_DEBUG)
                std::cerr << "memoryPool" << "allocate " << bytes << " Bytes\n";
#endif
                total += bytes;
                void* ret = upstream->allocate(bytes, alignment);
                return ret;
            }

            void do_deallocate(void* ptr, size_t bytes, size_t alignment) override {
#if defined (RAINBOY_DEBUG) && defined (MEMORY_DEBUG)
                std::cerr << "memoryPool" << "deallocate " << bytes << " Bytes\n";
#endif
                upstream->deallocate(ptr, bytes, alignment);
            }

            bool do_is_equal(const std::pmr::memory_resource& other) const noexcept
                override {
                    // same object?:
                    if (this == &other) return true;
                    // same type and prefix and equal upstream?:
                    auto op = dynamic_cast<const memoryPool*>(&other);
                    return op != nullptr && upstream->is_equal(other);
            }

    };


    //设定内存池与内存容量
    //template<std::size_t memoryPool_size>
    //TODO 128_mb 有可能超过题目的限制
#define set_memoryPool(memoryPoolSize) \
        std::array<std::byte,memoryPoolSize-4_mb> __buf; \
        std::pmr::monotonic_buffer_resource buff(__buf.begin(),__buf.size(),std::pmr::null_memory_resource()); \
        memoryPool myPool(&buff);
        //std::pmr::set_default_resource(&myPool);

#define memoryPool_init() std::pmr::set_default_resource(&myPool)

    
} // end namespace rainboy


#endif
