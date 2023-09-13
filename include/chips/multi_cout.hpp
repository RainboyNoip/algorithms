//平常在使用cout 输出内容的时候需要使用多个 << 这样感觉很不爽 🙁
//现在提供一个__cout的函数
//__cout(1,2,3,"hello world") --> `1 2 3 hello world\n`
// 可以输入多个参数,输出的数字之间添加空格

#include <iostream>

#if __cplusplus >= 201703L //c++17 以使用 fold expression

//使用c++17 fold expression ,输出每一个参数,并在中间加空格
template<typename... Args>
std::ostream & __out(std::ostream & out = std::cout,Args&&... args)
{
    ((out << args << ' '),...);
    return out;
}

#elif __cplusplus >=201103L

//使用c++11 递归的参数模板实现 

template<typename T>
std::ostream & __out(std::ostream& out = std::cout,T&& t1)
{
    out << t1;
    return out;
}

template<typename T,typename... Args>
std::ostream & __out(std::ostream& out = std::cout,T&& t1,Args&&... args)
{
    out << t1 << ' ';
    return __out(out,std::forward<Args>(args)...);
}

#endif
