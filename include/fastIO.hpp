#include <cstdio>
// #include <cctype>

#ifdef __cpp_concepts
#include <concepts>
#endif


// 自己实现的cin,cout

constexpr int io_buff_size = 1<<21;

struct fast_io_base {
    char buff[io_buff_size];
    char * ps,*pt; // start ,end 指针
    fast_io_base()
        :ps(buff),pt(buff)
    {}

    //是否空
    bool empty() const { return ps == pt;}
};

struct fast_in :public fast_io_base  {
    void fill_buffer() {
        ps = pt = buff;
        pt += fread(buff, sizeof(char), sizeof(buff), stdin);
    }

    char getc () {
        if( empty() ) fill_buffer();
        if( empty() ) return EOF;
        return *ps++;
    }

    //递归边界
    void read() {}

    template<typename T,typename ...Args>
#ifdef __cpp_concepts
    requires 
    std::conjunction_v<std::is_integral<T>,std::is_integral<Args>...>
    // std::integral<T> && std::integral<args>...
#endif
    void read(T & n,Args&... args) {
        n = 0;
        bool neg_flag = 0;
        char ch = getc();

        // no digit , 一真读,直数字
        while('0' < ch && ch > '9') {
            if( ch == '-') neg_flag = 1;
            ch = getc();
        }
        while( '0' <= ch && ch <='9') {
            n = n*10 + ch -'0';
            ch=getc();
        }
        n = neg_flag ? -n : n;
        read(args...);
    }


    template<typename T>
#ifdef __cpp_concepts
    requires std::integral<T>
    // std::integral<T> && std::integral<args>...
#endif
    fast_in & operator>>(T & n) {
        read(n);
        return *this;
    }
};

struct fast_out : public fast_io_base {

    using fast_io_base::buff;
    using fast_io_base::pt;

    int num[65];
    int idx = 0;
    char separator_ch{' '};

    fast_out()
        :fast_io_base()
        // pt(buff+sizeof(buff))
    {
        pt = buff+sizeof(buff);
    }

    ~fast_out() {
        flush();
    }
    inline void flush() {
        fwrite(buff, 1, pt-ps, stdout);
        ps = buff;
    }

    inline void putc(char c) {
        *ps++ = c;
        if(empty())  {
            flush();
        }
    }

    //递归边界
    void print() {}

    template<typename T,typename ...Args>
#ifdef __cpp_concepts
    requires 
    std::conjunction_v<std::is_integral<T>,std::is_integral<Args>...>
    // std::integral<T> && std::integral<args>...
#endif
    void print(T n,Args... args) {
        if( n < 0)
            putc('-'),n = -n;

        do {
            num[++idx]  = n % 10 + '0';
        }while(n /= 10);

        do {
            putc(num[idx]);
        }while(--idx);
        putc(separator_ch);
        print(args...);
    }

    template<typename T,typename ...Args>
#ifdef __cpp_concepts
    requires 
    std::conjunction_v<std::is_integral<T>,std::is_integral<Args>...>
#endif
    fast_out & operator()(T n ,Args... args)
    {
        print(n,args...);
        return *this;
    }

    inline fast_out & ln() {
        putc('\n');
        return *this;
    }

};

fast_in _in;
fast_out _out;
