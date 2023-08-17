//@desc 虚基类

#pragma once
#include <iostream>
#include <memory>


namespace Stream {
namespace provider{

template<typename T>
class StreamProvider {

public:
    struct Iterator;
    
    bool advance() {
        return advance_impl_ptr(this);
    }

    std::shared_ptr<T> get() {
        return get_impl_ptr(this);
    }

    Iterator begin();
    Iterator end();

    using advance_func_ptr = bool(*)(StreamProvider *);
    using get_func_ptr = std::shared_ptr<T>(*)(StreamProvider *);

protected:

    advance_func_ptr advance_impl_ptr;
    get_func_ptr get_impl_ptr;
};



template<typename T>
class StreamProviderProxy : public StreamProvider<T> {

public:
    template<typename Driv>
    StreamProviderProxy(const Driv *) {
        this->advance_impl_ptr = advance_impl_ptr_proxy<Driv>;
        this->get_impl_ptr = get_impl_ptr_proxy<Driv>;
    }

    template<typename Driv>
    static bool advance_impl_ptr_proxy(StreamProvider<T> * ptr)
    {
        return static_cast<Driv*>(ptr) -> advance_impl();
    }

    template<typename Driv>
    static std::shared_ptr<T> get_impl_ptr_proxy(StreamProvider<T> * ptr)
    {
        return static_cast<Driv*>(ptr) -> get_impl();
    }

};

// unique_ptr 指针
template<typename T>
using StreamProviderPtr = std::unique_ptr<StreamProvider<T>>;

//作用: 辅助函数,创建相应类型的Provider
template<template<typename...> class Provider,
         typename T,
         typename... TemplateArgs,
         typename... ConstructorArgs>
StreamProviderPtr<T> make_stream_provider(ConstructorArgs&&... args) {
    return StreamProviderPtr<T>(
        new Provider<T, TemplateArgs...>(
            std::forward<ConstructorArgs>(args)...));
}

}// namespace provider
} // namespace Stream


//迭代器
#include "StreamProviderIterator.h"

template<typename T>
typename Stream::provider::StreamProvider<T>::Iterator
Stream::provider::StreamProvider<T>::begin() {
    return Iterator::begin(this);
}

template<typename T>
typename Stream::provider::StreamProvider<T>::Iterator
Stream::provider::StreamProvider<T>::end() {
    return Iterator::end(this);
}
