/**
 * @file
 * @brief 父亲孩子表示法用来存树
 */
#include <unordered_map>
#include <forward_list>
#include "base.hpp"

//TODO
// 以邻接表的形式来存
// [node1] -> 2 ,3,4,5,6
// [node2] -> 4,5,6
// 
// 一个环形link list 
// std::list ?
namespace RALGO {

template<typename T>
struct ParentChildTreeNode {

    using ptr = ParentChildTreeNode*;

    ptr father;
    ptr child_link;
    ptr first_child;
    ptr last_child;

    T val;

};

template<typename T>
class ParentChildTree {

    using ptr = typename ParentChildTreeNode<T>::ptr;

    public:
        
        void append_child(int fa,int ch, T val) {

        }

        ptr get_root();

        
    private:
        std::unordered_map<int,>  __Map;

};

} // end namespace RALGO
