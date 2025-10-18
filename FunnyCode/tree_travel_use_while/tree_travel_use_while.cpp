/**
 * @file
 * @brief 不使用递归,使用while来对树进行 pre-order,middle-order,post-order
 */

/**
 * 算法的核心:
 * 当你进行入一点,发现了一个状态值,比如first_visit,表示:**你已经(刚刚)离开了那个状态(first_visit)**
 */

/**
 *   a
    / \
   b   c
  / \ / \
 d  e f  g

 */
#include <iostream>
#include <cstring>
#include <memory_resource>
#include <vector>

struct Node;
using NodePtr = Node *;
NodePtr root;

enum travel_status{
    first_visit,
    left_visit,
    right_visit
};


struct Node {
    NodePtr father;
    NodePtr lson,rson;
    char val;
    travel_status status;

    bool is_leaf() const {
        return lson == nullptr && rson == nullptr;
    }

    bool has_left_son() const {
        return lson != nullptr;
    }

    bool has_right_son() const {
        return rson != nullptr;
    }

    Node()
    {
        father = lson = rson = nullptr;
    }
};

struct NodePool {

    static Node __Nodes[1024];
    static int cnt;

    static void init() {
        cnt = 0;
        memset(__Nodes,0,sizeof(__Nodes));
    }
    static NodePtr get() {
        NodePtr p = new (&__Nodes[cnt++]) Node;
        return p;
    }
};

Node NodePool::__Nodes[1024];
int NodePool::cnt = 0;


void create_tree() {
    auto * a = NodePool::get();
    root = a;

    auto * b = NodePool::get();
    auto * c = NodePool::get();
    auto * d = NodePool::get();
    auto * e = NodePool::get();
    auto * f = NodePool::get();
    auto * g = NodePool::get();
    
    auto set_node = [](NodePtr u,NodePtr fa,char val) {
        u->father= fa;
        u->val = val;
    };
    auto set_lr_son = [](NodePtr u,NodePtr l, NodePtr r) {
        u->lson = l;
        u->rson = r;
    };

    set_node(a, nullptr, 'a');
    set_node(b, a, 'b');
    set_node(c, a, 'c');
    set_node(d, b, 'd');
    set_node(e, b, 'e');
    set_node(f, c, 'f');
    set_node(g, c, 'g');
    set_lr_son(a, b, c);
    set_lr_son(b, d, e);
    set_lr_son(c, f, g);
}

void pre_order() {
    auto current = root;
    current->status = first_visit;

    while ( current != nullptr ) {
        
        switch( current->status ){
            case first_visit: 
                current->status = left_visit;
                std::cout << current->val << " ";
                if (current->has_left_son() ) {
                    current = current->lson;
                    current->status = first_visit;
                }
                break;
            case left_visit:
                current->status = right_visit;
                if (current->has_right_son() ) {
                    current = current->rson;
                    current->status = first_visit;
                }
                break;
            case right_visit:
                current = current->father;
                break;
        }
    }
}

void middle_order() {
    auto current = root;
    current->status = first_visit;

    while ( current != nullptr ) {
        
        switch( current->status ){
            case first_visit: 
                current->status = left_visit;
                if (current->has_left_son() ) {
                    current = current->lson;
                    current->status = first_visit;
                }
                break;
            case left_visit:
                std::cout << current->val << " ";
                current->status = right_visit;
                if (current->has_right_son() ) {
                    current = current->rson;
                    current->status = first_visit;
                }
                break;
            case right_visit:
                current = current->father;
                break;
        }
    }
}

void post_order() {
    auto current = root;
    current->status = first_visit;

    while ( current != nullptr ) {
        

        switch( current->status ){
            case first_visit: 
                current->status = left_visit;
                if (current->has_left_son() ) {
                    current = current->lson;
                    current->status = first_visit;
                }
                break;
            case left_visit:
                current->status = right_visit;
                if (current->has_right_son() ) {
                    current = current->rson;
                    current->status = first_visit;
                }
                break;
            case right_visit:
                std::cout << current->val << " ";
                current = current->father;
                break;
        }
    }
}


int main(){
    create_tree();
    std::cout << "tree :\n "
<< 
"    a    \n"
"   / \\   \n"
"  b   c  \n"
" / \\ / \\ \n"
"d  e f  g\n"
        << "\n\n\n";

    std::cout<< "pre_order\n";
    pre_order();

    std::cout<< "\n\n";

    std::cout<< "middle_order\n";
    middle_order();
    std::cout<< "\n\n";

    std::cout<< "post_order\n";
    post_order();
    std::cout<< "\n";
    return 0;
}
