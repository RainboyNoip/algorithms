//A Node-positioning Algorithm for General Trees by JOHN Q. WALKER II
// paper is here : https://onlinelibrary.wiley.com/doi/abs/10.1002/spe.4380200705

#include <string>
#include <iostream>
#include <vector>
#include "draw_tree.hpp"

Draw_Tree mydr;
template<typename T>
struct Node;

const double level_separation = 100;
const int max_depth = 1024;
const double sibling_separtion = 40;
const double subtree_separtion = 4;

//所的点应该向右移值
const double all_move_right = 250;



//tree node
template<typename T>
struct Node {
    using ptr = Node *;
    ptr parent();
    ptr & first_child() { return childs.front();}
    ptr left_sibling() {
        ptr self = this;
        ptr fa = self->fa;
        if( fa == nullptr) return self;

        int i;
        for(i = 0 ;i < fa->childs.size() ; i++) {
            if( fa->childs[i] == self) break;
        }
        if( i == 0) return self;
        return fa->childs[i-1];
    }
    ptr right_sibling() {
        ptr self = this;
        ptr fa = self->fa;
        if( fa == nullptr) return self;

        int i;
        for(i = 0 ;i < fa->childs.size() ; i++) {
            if( fa->childs[i] == self) break;
        }
        if( i+1 == fa->childs.size()) return self;
        return fa->childs[i+1];
    }

    ptr & left_neightbor() { return m_left_neighbor;}

    bool is_leaf() const { return childs.empty();}

    bool has_right_sibling() {
        //右兄弟不为自己本身
        return right_sibling() != this;
    }

    bool has_left_sibling() {
        return left_sibling() != this;
    }

    double m_xcoord = 0;
    double m_ycoord = 0;
    double m_prelim = 0;
    double m_modifier = 0;

    T val;

    ptr fa = nullptr;
    std::vector<ptr> childs;

    ptr m_left_neighbor =nullptr;

    //输出信息

    friend std::ostream & operator<<(std::ostream & __o , const Node & node) {
        __o << "node : " << node.val 
            << " prelim: " << node.m_prelim
            << "\t modifier: " << node.m_modifier
            << "\t x: " << node.m_xcoord
            << "\t y: " << node.m_ycoord;
        return __o;
    }
};

using node = Node<char>;
using node_ptr = node::ptr;

int n;
node_ptr root = nullptr;
double xTopAdjustment = width/2;
double yTopAdjustment = 50.0;

node_ptr pre_node_at_level[max_depth] = {nullptr};

void apportion(node_ptr u,int dep) { 
}

double mean_node_size(node_ptr a,node_ptr b) {
    return R ;
}

//第一次在树上行走,得到每个结点的
// perlim modifier
void first_walk(node_ptr u,int dep) {
    // 记录: 左边的邻居
    u->left_neightbor() = pre_node_at_level[dep];
    pre_node_at_level[dep] = u;

    u->m_modifier = 0; //初始化 m_modifier -> 0

    // 条件1: 叶了结点 ,边界
    if( u->is_leaf() || dep == max_depth) {
        if( u->has_left_sibling() )
            u->m_prelim = u->left_sibling()->m_prelim
                            + sibling_separtion
                            + mean_node_size(u->left_sibling(), u);
        else // 没有左兄弟
            u->m_prelim = 0;

    }
    else { // 条件2 : 不是叶子
        node_ptr left_most,right_most;
        left_most = right_most = u -> first_child();

        // 先递归, pre_order
        first_walk(left_most, dep+1);

        //递归所有的孩子
        while( right_most->has_right_sibling() ) {
            right_most = right_most->right_sibling();
            first_walk(right_most, dep+1);
        }

        //孩子的宽度 / 2
        double mid = (left_most->m_prelim + right_most->m_prelim) / 2;
        
        //有左孩子,
        if( u->has_left_sibling() ) { 
            u->m_prelim = u->left_sibling()->m_prelim
                          + sibling_separtion
                          + mean_node_size(0, 0); //mean of node size 
            u->m_modifier = u->m_prelim - mid; //修饰

            // apportion(u,dep);
        }
        else // 没有左孩子,由孩子决定 m_prelim
            u->m_prelim = mid;
    }
}

bool second_walk(node_ptr u,int dep,double modSum) {
    if( dep >= max_depth) return false;
    double yTemp = yTopAdjustment + (dep * level_separation);
    u->m_ycoord = yTemp;
    u->m_xcoord = u->m_prelim + modSum;
    //输入second_work的信息
    std::cout << "node : " << u->val 
        << " x " << u->m_xcoord 
        << " \tmodSum: " << modSum
        << "\n";

    //遍历孩子
    for(node_ptr it : u->childs) {
        second_walk(it, dep+1, modSum + u->m_modifier);
    }

    return true;
}

bool position_tree(node_ptr root) {
    if( root == nullptr) return false;
    first_walk(root, 1);
    std::cout << "------- second_walk --------" << "\n";
    second_walk(root, 1, 0);
    return true;
}


node tree[1024];


//读取数据
void read_data() {
    //读取数据
    std::cin >> n;
    std::string str;
    std::getline(std::cin, str);
    for(int i=1;i<=n;++i){
        std::getline(std::cin, str);
        std::cout << i << " ";
        std::cout << str << "\n";
        auto u = &tree[str[0] - 'a'];
        auto v = &tree[str[2] - 'a'];
        u->childs.push_back(v);
        v->fa = u;
        u->val = str[0];
        v->val = str[2];
    }

    root = &tree[1];
    while( root->fa != nullptr)
        root = root->fa;
    //读取数据结束
}

//初始化

void init() {
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

void __dfs_draw_tree(node_ptr root) {
    if( root == nullptr) return;
    
    mydr.draw_one_node(root->m_xcoord+ all_move_right, root->m_ycoord, root->val);
    
    for( auto & e : root->childs)
        __dfs_draw_tree(e);
    std::cout << *root << "\n";

}

//根据写的得到的数据，渲染图片
void draw_tree(const std::string & filename) {
    __dfs_draw_tree(root);
    mydr.write_png(filename);
}

int main(int argc,char * argv[]){
    // std::cout << argc << "\n";
    if( argc == 1) {
        freopen("in", "r", stdin);
    }
    
    init();
    read_data();
    position_tree(root);

    draw_tree("1.png");

    if( argc == 1) {
        fclose(stdin);
    }
    return 0;
}
