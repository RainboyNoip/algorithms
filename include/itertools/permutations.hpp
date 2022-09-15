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


#ifndef  PERMUTATIONS_HPP_
#define PERMUTATIONS_HPP_

//#include "iterbase.hpp"

#include "iterbase.hpp"

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
    using IndexVector = std::vector< _Vp_iterator>;

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
        using iterator_category = std::input_iterator_tag;
        // using value_type = Permutable<ContainerT>;
        // using difference_type = std::ptrdiff_t;
        // using pointer = value_type*;
        // using reference = value_type&;
        // 存的值是 外部viewRange的iterator
        using ContainerType = ITER_WRAPPER::IterWrapper<_Vp_iterator> ;
        ContainerType m_Container;
                                 
        using ContainerIt = typename IndexVector::iterator;
        static constexpr const int COMPLETE = -1;
        int steps_;
        
        // static bool comp_iters(ContainerIt  & lhs ,ContainerIt & rhs){
        //     return **lhs < **rhs;
        // }

        static bool comp_iters(const _Vp_iterator & lhs ,const  _Vp_iterator & rhs){
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
            std::sort(m_Container.begin(),m_Container.end());
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


#endif
