#include "more_ranges.hpp"

namespace rainboy {

    using std::ranges::iterator_t;
    using std::ranges::sentinel_t;
    
//>>>>>>>>>>>>>>>>>>>> cycle_view
    template<std::ranges::view _Vp>
    class cycle_view : public std::ranges::view_interface<cycle_view<_Vp>>
    {
        private:
            
        public:
            struct sentinel;
            struct iterator {
                private:
                    friend sentinel;

                    using _Vp_iter = iterator_t<_Vp>; // 容器在Vp的迭代器类型
                    _Vp_iter _M_current = _Vp_iter(); // 初始化
                    cycle_view* _M_parent = nullptr;  // 指向cycle_view

                public:

                    using iterator_category = typename std::iterator_traits<_Vp_iter>::iterator_category;
                    using value_type = range_value_t<_Vp>;
                    using difference_type = range_difference_t<_Vp>;

                    iterator() = default;

                    constexpr iterator& operator++(); // ++it
                    //it++
                    constexpr void operator++(int) {  ++*this;  }

                    friend constexpr bool operator==(const iterator& l,const iterator& r)
                        requires std::equality_comparable<_Vp_iter>
                    {
                        return l._M_current == r._M_current;
                    }

                    friend constexpr bool operator!=(const iterator& l,const iterator& r)
                        requires std::equality_comparable<_Vp_iter>
                    {
                        return !(l._M_current == r._M_current);
                    }
            };

            struct sentinel{
            private:
                sentinel_t<_Vp> _M_end = sentinel_t<_Vp>(); // 
                constexpr bool __equal(const iterator & __i) const
                { return __i._M_current == _M_end;}
            public:
                sentinel() = default;
                constexpr explicit sentinel(cycle_view & _parent)
                    :_M_end(std::ranges::end(_parent._M_base) 
                    {}

                friend constexpr bool operator==(const iterator & _x ,const sentinel & _y )
                { return _y.__equal(_x);}
            };

    };
//<<<<<<<<<<<<<<<<<<<< cycle_view

} // end namespace rainboy
