#include <iostream>
#include <cstring>
#include "tidy.hpp"
#include "draw_tree.hpp"
using namespace RALGO;

/**
             a
            / \
           b   c
          / \   \
         d  e    f
           / \    \
          h   i    j
                  /
                 k
                / \
               l   m
              / \
             n   o
 */

using NodePtr = TidyDrawingsOftrees::TidyTreeNode<char>::TidyTreeNodePtr;
using Node = TidyDrawingsOftrees::TidyTreeNode<char>;
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


NodePtr root;
void create_tree() {
    NodePtr a = NodePool::get();
    NodePtr b = NodePool::get();
    NodePtr c = NodePool::get();
    NodePtr d = NodePool::get();
    NodePtr e = NodePool::get();
    NodePtr f = NodePool::get();
    NodePtr h = NodePool::get();
    NodePtr i = NodePool::get();
    NodePtr j = NodePool::get();
    NodePtr k = NodePool::get();
    NodePtr l = NodePool::get();
    NodePtr m = NodePool::get();
    NodePtr n = NodePool::get();
    NodePtr o = NodePool::get();

    auto set_node = [](NodePtr u,NodePtr fa,char val) {
        u->father= fa;
        u->val = val;
    };
    auto set_lr_son = [](NodePtr u,NodePtr l, NodePtr r) {
        u->lson = l;
        u->rson = r;
    };

    root = a;
    set_node(a, nullptr, 'a');
    set_node(b, a, 'b');
    set_node(c, a, 'c');
    set_node(d, b, 'd');
    set_node(e, b, 'e');
    set_node(f, c, 'f');
    set_node(h, e, 'h');
    set_node(i, e, 'i');
    set_node(j, f, 'j');
    set_node(k, j, 'k');
    set_node(l, k, 'l');
    set_node(m, k, 'm');
    set_node(n, l, 'n');
    set_node(o, l, 'o');

    set_lr_son(a, b,c);
    set_lr_son(b, d,e);
    set_lr_son(c, nullptr,f);
    set_lr_son(d, nullptr,nullptr);
    set_lr_son(e, h,i);
    set_lr_son(f, nullptr,j);
    set_lr_son(h, nullptr,nullptr);
    set_lr_son(i, nullptr,nullptr);
    set_lr_son(j, k,nullptr);
    set_lr_son(k, l,m);
    set_lr_son(l, n,o);
    set_lr_son(m, nullptr,nullptr);
    set_lr_son(n, nullptr,nullptr);
    set_lr_son(o, nullptr,nullptr);
}

    Draw_Tree mydr;
int main(){
    create_tree();

    TidyTreeFunc<char>(root, 7);
    //定义draw_tree(100)

    std::ifstream font("CamingoCode-Bold.ttf",std::ios::binary);
    if( !font ){
        std::cout << "cannot open font file" << "\n";
        return 0;
    }
    char t;
    while( font ) {
        font.read(&t, 1);
        font_a.push_back(t);
    }
    font.close();
    mydr.set_default_font();
    // mydr.write_png("test.png");

    //遍历这个树

    TidyDrawingsOftrees::TreeTravel<std::integral_constant<int,0b001>>(root, 
            [&mydr](NodePtr u,int h){
                std::cout << u->val << "\n";
                const int base = 50;
                const int mv = 100;
                if( u->lson)
                    mydr.draw_line(mv+ u->x * base, mv+ u->y*base, mv+ u->lson->x*base, mv+ u->lson->y*base);
                if( u->rson)
                    mydr.draw_line(mv+ u->x * base, mv+ u->y*base, mv+ u->rson->x*base, mv+ u->rson->y*base);
                mydr.draw_one_node(mv+ u->x * base,mv+ u->y*base,mv+ u->val);
            },
            0);

    mydr.write_png("tidy.png");
    
    return 0;
}

