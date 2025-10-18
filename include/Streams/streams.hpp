#pragma once

#include "providers/providers.hpp"

namespace Stream {

//@创建一个Stream容器
template<typename T>
class Streams {

public:
    using Iterator = typename StreamProvider<T>::Iterator;

    Iterator begin() {
        return source_.begin(); 
    }

    Iterator end() {
        return source_.end();
    }

    //数组
    template<std::size_t N>
    Streams(T (&arr)[N])
    {

    }

private:
    StreamProviderPtr<T> source_;
};

} // end namespace Stream

