/**
 * @file
 * @brief tree layout algorithm from 
 * Walker JQ II. A node-positioning algorithm for general trees. Software—Practice and Experience 1990; 20(7)685–705
 * Author:Rainboy
 * time: 2023-04-03 09:35
 */

#include <list>
#include <iostream>
#include <functional>
#include <memory>
#include <exception>
#include <memory_resource>


namespace RALGO {
    
namespace Walk_tree_draw_NS {
    
template<typename T>
struct Node {
    using NodePtr = Node *;

    NodePtr father;
    NodePtr left_neighbor;
    NodePtr left_slibing;
    NodePtr right_slibing;
    NodePtr first_child;
    NodePtr last_child;

    double x,y;
    double prelim,modifier;

    T val; //结点存的值
           //


    Node() {
        father =
            left_neighbor=
            left_slibing=
            right_slibing= first_child = nullptr;
    }
};


//Node<T>的输出 
template<typename T>
std::ostream& operator<<( std::ostream& os ,const Node<T> & node) {
    os << ">>Node: val: " << node.val 
        << " prelim: " << node.prelim
        << " modifier: " << node.modifier
        << " x:" << node.x
        << " y:" << node.y;
    return os;
}


} // end namespace Walk_tree_draw_NS



template<typename T,std::size_t MAXDEP=1024>
class walk_tree_draw {
    public:

        //type of tree nodes
        using Node = Walk_tree_draw_NS::Node<T>;
        using NodePtr = Node *;

        ~walk_tree_draw() {
            if( root == nullptr) return;
            _delete(root);
        }

        explicit walk_tree_draw(
                unsigned int SlibSepration,
                unsigned int LevelSeparation,
                unsigned int nodeSize,
                std::pmr::memory_resource * mr = std::pmr::get_default_resource()
                )
            :
            m_SlibSeparation(static_cast<double>(SlibSepration))
             ,m_SubtreeSeparation(m_SlibSeparation)
             ,m_LevelSeparation(static_cast<double>(LevelSeparation))
                ,m_nodeSize(static_cast<double>(nodeSize))
                ,m_alloc(mr)
                ,root{nullptr}
                ,m_level_ptr{MAXDEP+1,nullptr}
        {}

        // NodePtr createNode(T && val) {
        //     NodePtr t = m_alloc.allocate(1);
        //     t->val = std::move(val);
        //     return t;
        // }

        NodePtr createNode(T val) {
            void * pt = m_alloc.allocate(1);
            // NodePtr t = pt;
            NodePtr t = new (pt) Node;
            t->val = val;
            return t;
        }

        /**
         * @brief 向树中添加父亲与孩子
         *
         * @param fa NodePtr point to father 
         * @param ch NodePtr point to child 
         */
        void append_child(NodePtr fa,NodePtr ch) {
            ch->father = fa;
            if( !fa->first_child ) {
                fa->first_child =
                fa->last_child = ch;
            }
            else {
                fa->last_child->right_slibing = ch;
                ch->left_slibing = fa->last_child;
                ch->right_slibing = nullptr;
            }
            fa->last_child = ch;
            root = fa;
        }

        //@brief check root point to real root
        void check_root() {
            while( root->father != nullptr)
                root = root->father;
        }
        
        
        // @brief calculate tree layout
        bool postionTree() {
            check_root();
            first_walk(root, 0);
            second_walk(root, 0, 0.0f);
            return 1;
        }

        /**
         * @brief The procedure FIRSTWALK. In this first post-order walk, ez'eIy node of the tt-ee is assig~ed a 
         * preliminaiy x-co-ordinate (held in the jeld PRELIM(Node1). IPI additloii, iritental nodes ate giveri rriodifiers, 
         * which will be used to tnot:e their offspririg to the right (held in the field MODIFIER(Node))
         *
         * @param u 
         * @param level 
         */
        void first_walk(NodePtr u,int level){
            //  set nodeptr value at this level
            u->left_neighbor = get_prenode_at_level(level);
            get_prenode_at_level(level) = u;

            u->modifier = 0.0f;

            //叶子结点的操作
            if( is_leaf(u) || level == MAXDEP){
                u->prelim = relative_position(u,0.0f);
            }
            else { // 非叶子结点
                // each_child(u, [this,level](NodePtr u){ first_walk(u, level+1); });

                //递归 walk
                for( NodePtr t = u->first_child ; t != nullptr ; t = t->right_slibing) {
                    first_walk(t, level+1);
                }

                double Mid = (u->first_child->prelim + u->last_child->prelim) /2;
                
                u->prelim = relative_position(u,Mid);
                u->modifier = u->prelim -Mid;
                apportion(u, level);

            }
        }

        /**
         * @brief  The procedure APPORTION, part 2. This procedure cleans up the positioning qf small sibling 
         * subtrees, thus fixing the 'left-to-tight gluing' probleni eeident in earlier algorithms. \\%en irming a new 
         * subtree further and fuiiher to the right, gaps ma?' open up among smaller subtrees thut were preciously 
         * sandwiched between larger subtrees. Thus, when niozing the new, Iaqer subttee to the right, the distance 
         * it is moved is also apportioned to smaller, intetior subtwes, cwating a pleasing aesthetic placenient 
         *
         * @param u 当前结点
         * @param level 当前层
         */
        void apportion(NodePtr u,unsigned int level){

            NodePtr LeftMost = u->first_child;
            NodePtr Neighbor = LeftMost->left_neighbor;
            std::size_t DepthStop = MAXDEP - level;
            std::size_t CompareDepth = 1;

            while( LeftMost != nullptr &&
                    Neighbor != nullptr &&
                    CompareDepth <= DepthStop)
            {
                double leftModSum = 0; // Neighbor的modifier和
                double rightModSum = 0;// u的leftMost结点的modifier和
                NodePtr AncestorLeftMost = LeftMost;
                NodePtr AncestorNeightbor = Neighbor;
                //向上求 modifier的和
                for( int i =0 ;i < CompareDepth ;i++) {
                    AncestorLeftMost = AncestorLeftMost->father;
                    AncestorNeightbor = AncestorNeightbor -> father;

                    rightModSum += AncestorLeftMost->modifier;

                    leftModSum += AncestorNeightbor->modifier;

                }


                // (Neighbor) --- m_SubtreeSeparation --- (LeftMost)
                //
                // (Neighbor) --- m_SubtreeSeparation --- (LeftMost)
                //                                            +---------------> (Neighbor)
                //                                               subtraction
                double MoveDistance = Neighbor->prelim
                                      + leftModSum + m_SubtreeSeparation
                                      + mean_of_node_size(LeftMost, Neighbor)
                                      - (LeftMost->prelim + rightModSum);

                // >0 表示有overlap,需要移动
                if( MoveDistance > 0.0f) {
                    NodePtr tmp = u;
                    int left_sibling_cnt = 0;

                    //计算 和左边那个需要分隔的那个子树之间的兄弟的数量,包扎u本身
                    for( ; tmp != nullptr && tmp != AncestorNeightbor ; tmp = tmp->left_slibing ) {
                        left_sibling_cnt++;
                    }

                    //这之间有兄弟
                    if ( tmp != nullptr ) {

                        //分离的值
                        double portion = MoveDistance / left_sibling_cnt;

                        for( tmp = u; tmp != AncestorNeightbor ; tmp = tmp->left_slibing){
                            tmp->prelim += MoveDistance;
                            tmp->modifier += MoveDistance; //影响孩子
                            MoveDistance -= portion;
                        }
                    }
                    else { 
                        // u的左边没有兄弟
                        return;
                    }
                }

                CompareDepth++;

                //下一层
                if( is_leaf(LeftMost) )
                    LeftMost = get_left_most(u,0,CompareDepth);
                else
                    LeftMost = LeftMost->first_child;
                if( LeftMost != nullptr)
                    Neighbor = LeftMost ->left_neighbor;
            }
        }
        
        /**
         * @brief  The function SECONDWALK. During a second pre-oi-der walk, each node is giren a final x-coordinate by summing its preliminary x-co-ordinate and the modifiers of all the node’s ancestors. The y-coordinate depends on the height of the tree. I/ the actual position of an inteiiot- node is tight of its preliniinant 
         * place, the subtree mated at the node must be niozqed right to centre the sons around the father. Rather 
         * than immediately readjust all the nodes in the subtree, each node remembers the distance to the proz~isional 
         * place in a modifierfield (MODIFIER(Node)). In this second pass down the tree, ritod$ers alp accumulated 
         * and applied to ecey node. Retuins TRUE ;f no emrs, othetxise returns FALSE 
         *
         * @param u 
         * @param level 
         * @param modSum 
         */
        bool second_walk(NodePtr u,int level, double modSum) {
            if( level > MAXDEP ) return false;
            double xTemp = xTopAdj + u->prelim + modSum;
            double yTemp = yTopAdj + (level * m_LevelSeparation);
            if( !check_extents_range(xTemp,yTemp)) return false;

            u->x = xTemp;
            u->y = yTemp;
            bool result = true;

            //has_child
            auto ch = u->first_child;
            for( ; ch !=nullptr; ch = ch->right_slibing  ) {
                result = second_walk(ch, level+1, modSum + u->modifier);
                if( result == false)
                    break;
            }
            return result;
        }

    private:

        std::pmr::polymorphic_allocator<Node> m_alloc;
        std::vector<NodePtr> m_level_ptr;
        NodePtr root = nullptr;
        NodePtr m_levelZeroPtr;
        double m_SlibSeparation;
        double m_SubtreeSeparation;
        double m_LevelSeparation;
        double m_nodeSize;
        double xTopAdj;
        double yTopAdj;

        NodePtr& get_prenode_at_level(unsigned int level) {
            if( level < MAXDEP )
                return m_level_ptr[level];
            throw  std::invalid_argument(std::string("argument level must less ") + std::to_string(MAXDEP) +" at func:"+ __func__);
        }

        bool is_leaf(NodePtr u) const {
            return  u->first_child == nullptr;
        }
        bool has_left_sibling(NodePtr u) {
            return u->left_slibing != nullptr;
        }

        double mean_of_node_size(NodePtr a,NodePtr b) {
            int cnt = 3;
            if( a ) --cnt;
            if( b ) --cnt;
            return m_nodeSize / cnt;
        }

        bool check_extents_range(double x,double y) {
            return true;
        }

        template<typename F>
        void each_child(NodePtr u,F f) {
            NodePtr t = u->first_child;
            for( ;t!=nullptr; t= t->right_slibing) {
                f(t);
            }
        }

        double relative_position(NodePtr u,double def= 0.0f) {
            if( has_left_sibling(u))
                return u->left_slibing->prelim 
                        + m_SlibSeparation
                        + mean_of_node_size(u->left_slibing, u);
            return def;
        }
        
        /**
         * @brief 得到 u的第level层的leftMost
         *
         * @param u 
         * @param level 
         * @return 
         */
        NodePtr get_left_most(NodePtr u,int nowDep,int level) {
            if( nowDep == level )
                return u;
            if( u ==nullptr)
                return  nullptr;
            
            for( NodePtr t = u->first_child ; t != nullptr ; t = t->right_slibing) {
                NodePtr ans = get_left_most(t, nowDep+1, level);
                if( ans != nullptr)
                    return ans;
            }
            return nullptr;
        }

        //递归的删除每个点所占的内存
        void _delete(NodePtr u) {
            if( u == nullptr) return;

            for( NodePtr t = u->first_child ; t !=nullptr ; t=t->right_slibing)
                _delete(t);
            m_alloc.deallocate(u, 1);
        }


    public:
        
        NodePtr first_child(NodePtr u) const {
            return u->first_child;
        }

        NodePtr left_sibling(Node u) const {

        }

        void set_root(NodePtr u ) {
            root = u;
        }

        using travelFuncType = std::function<void(NodePtr,NodePtr,int)>;

        void __debug_this_tree(NodePtr fa,NodePtr u,int level, travelFuncType & f) {
            for( NodePtr t = u->first_child ; t!=nullptr ; t=t->right_slibing) {
                __debug_this_tree(u,t,level+1,f);
            }
            //post order
            f(fa,u,level);
        }

        //输出树上的每个点的位置
        void debug_all_node_postion(

                travelFuncType func
                        =
                 [](NodePtr fa,NodePtr u,int level) {
                    std::cout << "LEVEL : " << level << " ";
                    std::cout << *u << "\n";
                 }

                ) {
            if( root != nullptr)
                __debug_this_tree(nullptr,root, 0,func);
        }

        void set_xy_top(double Xtop,double Ytop){
            xTopAdj = Xtop;
            yTopAdj = Ytop;
        }

};




} // end namespace RALGO

