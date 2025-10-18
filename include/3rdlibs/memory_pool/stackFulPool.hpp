//栈型内存池

struct StackfulPoolArg {
    char *m_base;
    char *m_guard;
};


struct StackfulPool {
    char *m_base;
    char *m_guard;

    //申请器
    template<typename T>
    struct StackfulAllocator;

    //字节大小的申请器
    auto get_allocator_for_task();

    // 构造函数
    StackfulPool(std::size_t sz);

    //析构函数
    ~StackfulPool();

    [[noreturn]]
    static void throw_exception() {
        throw  std::bad_alloc();
    }

    //向上对齐
    static std::size_t up_round(std::size_t sz, std::size_t align);

    //申请内存
    void allocate(std::size_t bytes, std::size_t alignment = alignof(std::max_align_t));

    //释放内存
    void deallocate(void *p , std::size_t bytes, std::size_t alignment = alignof(std::max_align_t));
};


