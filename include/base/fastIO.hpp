/**
 *
 * 自己实现的cin,cout,高速读取数据
 * fast_in 使用,全局实例 in,使用
 *  in(a)
 *  in(a,b,c)
 *  in >> a >> b >> c;
 *                                 
 *  int a[10]
 *  in(a+1,a+1+10);
 *                                 
 *                                 
 * fast_out 使用,全局实例 out
 * out.print(a)
 * out.print(a,b,c) //中间带有空格
 *
 * out.println(a)
 * out.println(a,b,c) 中间带有空格,最后换行
 *
 * out << a << b << c;
 * 
 * int a[10]
 * out(a+1,a+1+10); //输出数组
 *
 *
 */

#pragma once
#ifndef  __FAST_OUT_
#define  __FAST_OUT_
#include "base.hpp"

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

    template<typename T,typename ...Args,
    std::enable_if_t<
        std::conjunction_v<std::is_integral<T>,std::is_integral<Args>...>
    ,int> = 0
    >
// #ifdef __cpp_concepts
//     requires 
//     std::conjunction_v<std::is_integral<T>,std::is_integral<Args>...>
//     // std::integral<T> && std::integral<args>...
// #endif
    void read(T & n,Args&... args) {
        n = 0;
        bool neg_flag = 0;
        char ch = getc();

        // no digit , 一真读,直数字
        while(ch < '0' || '9' < ch ) {
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

    template<typename... T>
    void operator()(T&... args){
        read(args...);
    }
};

struct fast_out : public fast_io_base {

    using fast_io_base::buff;
    using fast_io_base::pt;
    using fast_io_base::ps;
    // ps 表示可以写的位置
    // pt 保持末尾不变

    int num[65];

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
        if( ps == buff) return;
        fwrite(buff, 1, ps-buff, stdout);
        ps = buff;
    }

    inline void putc(char c) {
        *ps++ = c;
        if(empty()) { //empty() 在这里表示可写空间
            flush();
        }
    }

    template<char sep=' '>
    inline void print() {}

    template<char sep=' '>
    inline void println() {}

    //递归边界
    template<typename T,std::enable_if_t< std::is_integral_v<std::remove_cvref_t<T>> ,int> = 0 >
    void print_one(T n) {
        if constexpr( std::is_same_v<T,char>) { //是一个字符类型
            putc(n);
        }
        else {
            // std::remove_cvref_t<T> n = nn;
            int idx = 0;
            if( n < 0)
                putc('-'),n = -n;

            do {
                num[++idx]  = n % 10 + '0';
            }while(n /= 10);

            do {
                putc(num[idx]);
            }while(--idx);
        }
    }

    void print_one(const std::string & str) {
        for(char c: str)
            print_one(c);
    }

    // //递归边界, char 字符
    // template<typename T ,std::enable_if_t<std::is_same_v<T,char>,int> = 0 >
    // void print_one(T c) {
    //     putc(c);
    // }

    //tuple的支持
    template<char sep=' ',typename... T>
    void print_one(const std::tuple<T...> & tup) {
        [&]<std::size_t... I>(std::index_sequence<I...>){
            print<sep>(std::get<I>(tup)...);
        }(std::make_index_sequence<sizeof...(T)> {});
    }


    //输出字符串
    template<std::size_t N>
    void print(const char (&str)[N]){
        for(int i = 0;i<N && str[i]!='\0'; ++i )
        {
            print_one(str[i]);
        }
    }

    //输出字符串
    template<std::size_t N>
    void println(const char (&str)[N]){
        print(str);
        ln();
    }

    template<char sep = ' ',typename Iter>
        requires requires(Iter it) {
            {*it};   // it can be dereferenced.
            {++it};  // it can be incremented.
        }
    void print(Iter begin,Iter end) {
        for( auto i = begin ; i != end ;++i){
            print_one(*i);
            putc(sep);
        }
    }


    // //是一个range,也就是有begin,end
    // template<typename Range>
    //     requires requires (Range r) {
    //         r.begin();
    //         r.end();
    //     }
    // void print(Range&& r) {
    //     print<' '>(r.begin(),r.end());
    // }

    // template<typename Range>
    //     requires requires (Range r) {
    //         r.begin();
    //         r.end();
    //     }
    // void println(Range&& r) {
    //     println(r.begin(),r.end());
    // }


    template<char sep = ' ',typename Iter>
        requires requires(Iter it) {
            {*it};   // it can be dereferenced.
            {++it};  // it can be incremented.
        }
    void println(Iter begin,Iter end) {
        for( auto i = begin ; i != end ;++i){
            print_one(*i);
            putc(sep);
        }
        ln();
    }

    template<char sep = ' ',typename T,typename ...Args
        // ,typename = std::void_t<decltype(print_one(std::declval<T>()))>
    >
    void print(T&& n,Args&&... args) {
        print_one(std::forward<T>(n));
        // if constexpr (sizeof...(args)!= 0) //!!! 我们的print有一个特点,就是每输出一个数,后面都会加一个空格 
            putc(sep);
        print<sep>(std::forward<Args>(args)...);
    }

    template<char sep = ' ',typename T,typename ...Args>
    void println(T&& n,Args&&... args) {
        print_one(std::forward<T>(n));
        if constexpr (sizeof...(args)!= 0)
            putc(sep);
        else
            ln(); //换行
        println<sep>(std::forward<Args>(args)...);
    }

    template<typename ...Args>
    fast_out & operator()(Args&&... args)
    {
        print(std::forward<Args>(args)...);
        return *this;
    }

    inline fast_out & ln() {
        putc('\n');
        return *this;
    }

    inline fast_out & sp() { //输出一个空格
        putc(' ');
        return *this;
    }
};

// template<typename T>
fast_out & operator<<(fast_out & out,const int & a) {
    out.print(a);
    return out;
}

template<typename T>
fast_out & operator<<(fast_out & out,T & a) {
    out.print(a);
    return out;
}

//tuple
// template<typename... T>
// fast_out & operator<<(fast_out & out,const std::tuple<T...> & tup) {
//     [&tup,&out]<std::size_t... I>(std::index_sequence<I...>){
//         out.println(std::get<I>(tup)...);
//     }(std::make_index_sequence<sizeof...(T)> {});
//     return out;
// }

fast_in in;
fast_out out;
#endif
