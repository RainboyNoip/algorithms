#include "more_ranges.hpp"

namespace rainboy {
    
//>>>>>>>>>>>>>>>>>>>> cycle_view
    template<std::ranges::view _Vp>
    class cycle_view : public std::ranges::view_interface<cycle_view<_Vp>>
    {

    };
//<<<<<<<<<<<<<<<<<<<< cycle_view

} // end namespace rainboy
