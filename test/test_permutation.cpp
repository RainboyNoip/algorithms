#include "catch_amalgamated.hpp"
#include "more_ranges.hpp"
#include "utils/type_name.hpp"

using namespace std;

TEST_CASE( "permutations", "[more_ranges.hpp]" ) {

    std::vector<int> v {4,3,2,1};
    std::ranges::ref_view ref(v);

    std::cout << "v -> " ;
    std::ranges::copy(v,std::ostream_iterator<int>(std::cout," "));
    std::cout << "\n";

    rainboy::Permuter_view<decltype(ref)> per(ref);

    auto Iter = per.begin();

    // for (auto& e : ref) {
    //     std::cout << e << std::endl;
    // }

    std::vector<int> v2;
    v2.reserve(v.size());
    // permutor 是 * Iterator 之后的内容
    // 也就是Iterator 内部的容器 IterWrapper
    
    std::cout << rainboy::type_name<decltype(Iter)>() << "\n";
    for( int & permutor_number: *Iter){
        // std::ranges::copy(permutor,std::back_inserter(v2));
        v2.push_back(permutor_number);
    }

    std::cout << "v -> " ;
    std::ranges::copy(v,std::ostream_iterator<int>(std::cout," "));
    std::cout << "\n";

    std::cout << "v2-> " ;
    std::ranges::copy(v2,std::ostream_iterator<int>(std::cout," "));
    std::cout << "\n";
    std::ranges::reverse(v2);

    REQUIRE(std::ranges::equal( v, v2 ));

    v2.clear();
    int count = 0;
    for( auto & p : v | rainboy::permutations ){
        ++count;
        //std::ranges::copy(p,std::back_inserter(v2));
        std::ranges::copy(p,std::ostream_iterator<int>(std::cout," "));
        std::cout << "\n";
    }

    REQUIRE( count == 4*3*2*1 ); // 排列的个数
    

}
