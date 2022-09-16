//对ranges进行拓展
#ifndef __MORE_RANGES__
#define __MORE_RANGES__

// #include "../base.hpp"

#include <iostream>
#include <vector>
#include <memory>
#include <ranges>
#include <algorithm>


namespace rainboy {

//>>>>>>>>>>>>>>>>>>>> iterator_wrapper


//<<<<<<<<<<<<<<<<<<<< iterator_wrapper end

//>>>>>>>>>>>>>>>>>>>> iteratoriterator
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

        //一个容器,所存的值是另个一个容器在的IteratorIteror
        template<typename IterType>
        class IterWrapper {
            public:
                using Container_type= std::vector<IterType>;
            private:
                using size_type = typename Container_type::size_type;


                Container_type _container;

            public:

                //迭代器类型
                using iterator = IteratorIteror<typename Container_type::iterator>;
                using const_iterator = IteratorIteror<typename Container_type::const_iterator>;
                using value_type = typename iterator::value_type;

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

// 排列
//
//
// 使用:
//
// vector<int> v = { 1,2,3};
//
// 1.  全排列
// for (auto&& vec : permutations(v)) {
//     for (auto&& i : vec) {
//         cout << i << ' ';
//     }
//     cout << '\n';
// }
//
// 得到v的全排列,输出:
// 1 2 3
// 1 3 2
// 2 1 3
// 2 3 1
// 3 1 2
// 3 2 1
//
// 2.  部分排列
// for (auto&& vec : permutations(v,2)) {
//     for (auto&& i : vec) {
//         cout << i << ' ';
//     }
//     cout << '\n';
// }
//
// 得到v的部分排列,输出:
// 1 2
// 1 3
// 2 1
// 2 3
// 3 1
// 3 2


namespace rainboy{

    using  namespace std::ranges;

    inline namespace iter {
        namespace impl {

            template<typename Container>
            class Permuter;

        } // end namespace impl
    } // end namespace iter
      //

template<view _Vp>
class Permuter_view : public view_interface<Permuter_view<_Vp>> {

private:
    // using _Vp_iterator = typename std::iterator_traits<std::remove_cv_t<_Vp>>::iterator;
    using _Vp_iterator = std::ranges::iterator_t<_Vp>;

    _Vp m_vp;
    int m_count;

public:

    constexpr
    Permuter_view(_Vp vp) :Permuter_view(std::move(vp),0) {}

    constexpr
    Permuter_view(_Vp vp,int count)
    : m_vp(std::move(vp)),m_count(count)
    {
        // if(count >=0)
        //     m_Container.reserve(count);
        // else
        //     m_Container.reserve(m_vp.size());
        // auto vp_it = vp.begin();
        // int i = 0;
        // for(auto & it : m_Container)
        //     it = std::make_pair(i++, vp_it++);
    }

    struct Iterator {
        // using value_type = Permutable<ContainerT>;
        // 存的值是 外部viewRange的iterator
        using ContainerType = ITER_WRAPPER::IterWrapper<_Vp_iterator> ;
        using ContainerIterator = typename ContainerType::iterator;
        using ContainerValuetype = typename ContainerType::value_type;

        using value_type = ContainerType;
        using iterator_category = std::input_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using pointer = value_type*;
        using reference = value_type&;


        ContainerType m_Container;
        // m_Container 容器的迭代器类型是?
                                 
        static constexpr const int COMPLETE = -1;
        int steps_;
        
        // static bool comp_iters(ContainerIt  & lhs ,ContainerIt & rhs){
        //     return **lhs < **rhs;
        // }

        using Inner_ContainerValueType = typename ContainerType::Container_type::value_type;
        static bool comp_iters(const Inner_ContainerValueType & lhs ,const  Inner_ContainerValueType & rhs){
            return *lhs < *rhs;
        }

        Iterator(_Vp & vp,int step = 0) :steps_(step)
        {
            if( steps_ == 0)
                m_Container.reserve(std::ranges::size(vp));
            else if( steps_ == COMPLETE) //不需要进行初始化
                return;
                //TODO particle choose
                ;
            auto it = std::ranges::begin(vp);
            auto end = std::ranges::end(vp);
            while ( it != end ) m_Container.get().push_back(it++);

            // auto x1 = m_Container.begin();
            // auto x2 = x1++;
            // std::cout << 
            //     comp_iters(x1, x2) <<" "
            //     << **x1 << " "
            //     << **x2
            //     << std::endl;

            // std::sort(m_Container.begin(),m_Container.end(),comp_iters);
            std::sort(m_Container.get().begin(),m_Container.get().end(),comp_iters);
        }

        //
        ContainerType & operator*() { return m_Container; }

        bool operator==(const Iterator & rhs) const { return !(*this != rhs);}
        bool operator!=(const Iterator & rhs) const { return steps_ != rhs.steps_; }

        Iterator& operator++(){
            ++steps_;
            if( !std::next_permutation(m_Container.begin(), m_Container.end()) )
                steps_ = COMPLETE;
            return *this;
        }

        Iterator operator++(int) {
            auto it = *this;
            ++*this;
            return it;
        }

    };

    Iterator begin() { return {m_vp,m_count};}
    Iterator end() {return {m_vp,-1};}
};

template<std::ranges::range _Vp>
Permuter_view(_Vp&&) -> Permuter_view<std::ranges::views::all_t<_Vp>>;

struct __Permutor  {

    template<std::ranges::range Range>
    decltype(auto) operator()(Range&& r) const{
        return Permuter_view{std::forward<Range>(r)};
    }

    template<std::ranges::range Range>
    friend decltype(auto) operator|(Range && __r,const __Permutor & __p) {
        //return __p.operator()(std::forward<Range>(__r));
        return __p(std::forward<Range>(__r));
    }
};

inline constexpr __Permutor permutations{};


} // end namespace rainboy



namespace std {
    namespace ranges {
        namespace views {

            // inline constexpr __adaptor::_RangeAdaptorClosure my_permutation 
                // = []<viewable_range _Range>(_Range&& __r){
                    // return rainboy::Permuter_view{std::forward<_Range>(__r)};
                // };

        }
    }
}

#endif //#define __MORE_RANGES__
