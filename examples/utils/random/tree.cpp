#include "base.hpp"
#include "utils/random/tree.hpp"

using namespace __random;
int main(){
    tree mytree(6); //创建了一个5个点的随机树
    auto t = std::make_tuple(1,2);
    // out.println(mytree.begin(),mytree.end()); //输出树
    out.println(mytree);
    // out.print_one(t);
    return 0;
}
