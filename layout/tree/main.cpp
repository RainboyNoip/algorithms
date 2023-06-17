#include <iostream>
#include <vector>
#include <list>
#include "walk.h"
#include "draw_tree.hpp"
// #include "clock.hpp"

using namespace RALGO;

int n;
Draw_Tree mydr;

// xsep,
// walk_tree_draw<char,1024> myTreeLayout(40,150,20);
walk_tree_draw<char,1024> myTreeLayout(100,150,20);
using nodeptr = walk_tree_draw<char, 1024>::NodePtr;

std::vector<std::list<int>> raw_tree_;

//读取数据
void dfs_tree(int u,int fa,nodeptr faPtr)
{
    for( auto v :raw_tree_[u]  ) {
        if( v == fa) continue;
        std::cout << char(u+'a') <<' ' <<  char(v+'a') << "\n";

        char ch = v+'a';
        auto ptr  = myTreeLayout.createNode(ch);
        myTreeLayout.append_child(faPtr, ptr);
        
        dfs_tree(v, u,ptr);
    }
}


void canvas_init() {
    std::ifstream font("CamingoCode-Bold.ttf",std::ios::binary);
    if( !font ){
        std::cout << "cannot open font file" << "\n";
        return;
    }
    char t;
    while( font ) {
        font.read(&t, 1);
        font_a.push_back(t);
    }
    font.close();
    mydr.set_default_font();
    // mydr.write_png("test.png");
}

int main(){
    std::cout << "start " << "\n";
    raw_tree_.resize(1000);
    canvas_init();
    myTreeLayout.set_xy_top(600, 80);
    // myTreeLayout.set_xy_top(0, 0);

    // step 1 , read tree data
    {
        //读取数据
        std::cin >> n;
        std::string str;
        std::getline(std::cin, str);
        for(int i=1;i<=n;++i){
            std::getline(std::cin, str);
            auto u = str[0] - 'a';
            auto v = str[2] - 'a';
            raw_tree_[u].push_back(v);
        }
        auto faPtr = myTreeLayout.createNode('o');
        myTreeLayout.set_root(faPtr);
        dfs_tree('o'-'a',-1, faPtr);
    }

    myTreeLayout.postionTree();
    myTreeLayout.debug_all_node_postion();

    //绘制树
    //
    myTreeLayout.debug_all_node_postion(
            [](nodeptr fa,nodeptr u,int level) {
                if(fa != nullptr) 
                    mydr.draw_line(fa->x, fa->y, u->x, u->y);
                mydr.draw_one_node(u->x, u->y, u->val);
            }
    );
    mydr.write_png("1.png");
    std::cout << "write tree to 1.png" << "\n";

    return 0;
}
