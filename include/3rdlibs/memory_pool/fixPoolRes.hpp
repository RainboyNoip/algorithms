//每次申请的内存大小都是固定的

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
