//公用的工具类
#ifndef ITERABASE_HPP_
#define ITERABASE_HPP_

// #include "../base.hpp"

#include <iostream>
#include <vector>
#include <memory>
#include <ranges>
#include <algorithm>


//>>>>>>>>>>>>>>>>>>>> iterator_wrapper


//<<<<<<<<<<<<<<<<<<<< iterator_wrapper end

//>>>>>>>>>>>>>>>>>>>> iteratoriterator
namespace rainboy {
    namespace ITER_WRAPPER {


        // 一个迭代器,是对另一个迭代器的包装
        // 实现的功能就是相当于直接用另一个迭代器
        //      container B       container A
        //
        //       [iterA1,            [1,2,3]
        //        iterA2,..]
        //          |
        //          |
        //          v
        // B.begin() -> IterType
        // IteratorIteror x(IterType)
        //
        template<typename IterType>
        class IteratorIteror {
            private:
                IterType sub_iter;
            public:
                using iterator_category = std::random_access_iterator_tag;
                using value_type = std::remove_reference_t<decltype(**std::declval<IterType>())>;
                using difference_type = std::ptrdiff_t;
                using pointer = value_type*;
                using reference = value_type&;

                IteratorIteror() = default;
                IteratorIteror(const IterType& it) : sub_iter{it} {}

                const IterType & get() const { 
                    return sub_iter;
                }

                bool operator!=(const IteratorIteror & other) const {
                    return this->sub_iter != other.sub_iter;
                }

                bool operator==(const IteratorIteror & other) const {
                    return !(*this != other);
                }

                decltype(auto) operator-(const IteratorIteror & rhs) const {
                    return this->sub_iter - rhs.sub_iter;
                }

                decltype(auto) operator->() const  {
                    return *this->sub_iter;
                }

                IteratorIteror& operator+=(difference_type n){
                    this->sub_iter+=n;
                    return *this;
                }

                IteratorIteror operator+(difference_type n){
                    auto it = *this;
                    it+=n;
                    return it;
                }

                IteratorIteror& operator-=(difference_type n){
                    this->sub_iter-=n;
                    return *this;
                }

                IteratorIteror operator-(difference_type n){
                    auto it = *this;
                    it-=n;
                    return it;
                }

                IteratorIteror& operator++(){
                    ++ this->sub_iter;
                    return *this;
                }

                IteratorIteror& operator--(){
                    -- this->sub_iter;
                    return *this;
                }

                IteratorIteror& operator++(int){
                    auto ret = *this;
                    ++*this;
                    return ret;
                }

                IteratorIteror& operator--(int){
                    auto ret = *this;
                    --*this;
                    return ret;
                }

                auto operator*() -> decltype(auto)
                { return **this->sub_iter;}

                auto operator*() const -> decltype(auto)
                { return **this->sub_iter;}

                bool operator<(const IteratorIteror & rhs) const 
                { return this->sub_iter < rhs.sub_iter; }

                bool operator<=(const IteratorIteror & rhs) const 
                { return this->sub_iter <= rhs.sub_iter; }

                bool operator>(const IteratorIteror & rhs) const 
                { return this->sub_iter > rhs.sub_iter; }

                bool operator>=(const IteratorIteror & rhs) const 
                { return this->sub_iter >= rhs.sub_iter; }
        };

        template<typename IterType>
        IteratorIteror(IterType & ) -> IteratorIteror<IterType>;

        //一个容器,所存的值是另个一个容器在的Iterator
        template<typename IterType>
        class IterWrapper {
            private:
                using Container_type= std::vector<IterType>;
                using size_type = typename Container_type::size_type;


                Container_type _container;

            public:

                using iterator = IteratorIteror<typename Container_type::iterator>;
                using const_iterator = IteratorIteror<typename Container_type::const_iterator>;

                IterWrapper() = default;

                IterWrapper(size_type sz) : _container(sz) {}

                void reserve(size_type sz) { _container.reserve(sz);}

                decltype(auto) size() const { return _container.size();}

                Container_type & get() { return _container;}

                auto operator[](size_type pos) noexcept -> decltype(auto)
                { return *_container[pos]; }

                bool empty() const noexcept {
                    return _container.empty();
                }

                iterator begin() { return {_container.begin()}; }

                const_iterator begin() const { return {_container.begin()}; }

                const_iterator cbegin() const { return {_container.cbegin()}; }

                iterator end() { return {_container.end()}; }

                const_iterator end() const { return {_container.end()}; }

                const_iterator cend() const { return {_container.cend()}; }

                iterator rbegin() { return {_container.rbegin()}; }

                iterator rend() { return {_container.rend()}; }
        };
        
    } // end namespace ITER_WRAPPER
    
} // end namespace rainboy
//<<<<<<<<<<<<<<<<<<<< iteratoriterator end

#endif
