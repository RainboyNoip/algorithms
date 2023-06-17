/**
 * @file
 * @brief Tidy drawings of trees from 
 *
 * https://ieeexplore.ieee.org/document/1702661
 * C. Wetherell and A. Shannon, "Tidy Drawings of Trees," in IEEE Transactions on Software Engineering, vol. SE-5, no. 5, pp. 514-520, Sept. 1979, doi: 10.1109/TSE.1979.234212.
 */

/**
 * 最原始的思想:左偏树
 * 以下原则构建一个左偏树
 *
 * 同一层的节点,都一行上,
 * 同一行的节点都必须至少相距离2,这个相距可以理解一种斥力
 * 同一行的节点都向左去,除非受到左边点的斥力,或孩子的力(修正值)
 *
 * 这样就行成了一种左偏树,
 *
 * 根据孩子可以得到每个点的修正值,可以根据修正值来修正孩子的位置,
 * 最后就行成了一种好看的二叉树
 *
 * next_pos[h] 这一层的下一个点的位置
 * modider[h] 为什么???? 要取最大值呢?
 * place 这个点的理论位置
 *
 */

#pragma once
#include <vector>
#include <type_traits>

namespace RALGO {


    namespace TidyDrawingsOftrees {
        enum nodeStatus  {
            first_visited,
            left_visited,
            right_visited
        };
        
        template<typename T>
        struct TidyTreeNode {
            using TidyTreeNodePtr = TidyTreeNode *;
            TidyTreeNodePtr father,lson,rson;
            T val;
            int x,y; //坐标
            int modifier;
            nodeStatus status;

            inline bool has_left_son() const {
                return  lson != nullptr;
            }
            inline bool has_right_son() const {
                return rson != nullptr;
            }

            inline bool is_leaf() const {
                return !has_left_son() && !has_right_son();
            }
        };


        struct Info {
            int modifier; // modifier of this level
            int next_pos; // next_pos of this level
        };

        template<typename UseFuncMode,typename Func1,typename Func2,typename Ptr>
        void TreeTravel(Ptr cur,Func1 first_func,Func2 right_func) {
            using namespace TidyDrawingsOftrees;
            cur->status = first_visited;
            int h = 0;
            while ( cur ) {
                switch ( cur->status) {
                    case first_visited:
                        if constexpr ( UseFuncMode::value & 0b001)
                            first_func(cur,h);
                        cur->status = left_visited;
                        if( cur->lson ) {
                            h++;
                            cur = cur->lson;
                            cur->status = first_visited;
                        }
                        break;
                    case left_visited:
                        cur->status = right_visited;
                        if( cur->rson ) {
                            h++;
                            cur = cur->rson;
                            cur->status = first_visited;
                        }
                        break;
                    case right_visited:
                        if constexpr ( UseFuncMode::value & 0b100 )
                            right_func(cur,h);
                        h--;
                        cur = cur->father;
                        break;
                }
            }
        };

    } // end namespace TidyDrawingsOftrees

    template<typename T>
    using TidyTreeNodePtr = typename TidyDrawingsOftrees::TidyTreeNode<T>::TidyTreeNodePtr;

    template<typename T>
    void TidyTreeFunc(TidyTreeNodePtr<T> root,std::size_t const maxHeight)  {
        using Ptr = TidyTreeNodePtr<T>;
        //allocate Memory
        std::vector<TidyDrawingsOftrees::Info> __lvl(maxHeight+5);

        // using FuncType = std::function<void(Ptr,int)>;


        using namespace TidyDrawingsOftrees;
        //first travel, set node' x and modifier
        TreeTravel<std::integral_constant<int,0b100>>
            (root,
            0, //not perform
            [&__lvl](Ptr cur,int h){
                int place = 0;
                if( cur->is_leaf() )
                    place = __lvl[h].next_pos; //叶子结点不受孩子的影响
                else if ( !cur->has_left_son() ) //只有右孩子
                    place = cur->rson->x - 1;
                else if( !cur->has_right_son()) //只有左孩子
                    place = cur->lson->x +1;
                else //有两个孩子
                    place = (cur->lson->x + cur->rson->x) /2;

                // if place is on left side of next_pos[h]
                __lvl[h].modifier = std::max(__lvl[h].modifier,__lvl[h].next_pos-place);
                /// ?? 这一句不理解,为什么modider 的位置只能变大呢
                
                //为什么叶子不受这一层modifier影响呢?
                cur->x = cur->is_leaf() ? place  : place + __lvl[h].modifier;
                __lvl[h].next_pos = cur->x + 2;
                cur->modifier = __lvl[h].modifier;
            }
        );

        int modSum = 0;
        TreeTravel<std::integral_constant<int,0b111>>
        ( root,
        [&__lvl,&modSum](Ptr cur,int h){
            cur->x += modSum;
            modSum += cur->modifier;
            cur->y = h*2+1;
        },
        [&modSum](Ptr cur,int h) {
            modSum -= cur->modifier;
        });


        //second travel

    }

    
} // end namespace RALGO
