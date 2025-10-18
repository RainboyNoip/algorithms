//线段树
//0 普通线段树
//1 动态开点线段树
//2 值域线段树


#include "base/macro.hpp"



//动态开点线段树
template<
    typename  T,
    typename PushUpType,
    typename PushDownType,
    typename MergeLeafType,
    std::size_t N = maxn>
struct dynamic_segment_tree {

    struct tree_node {
        int lc,rc;
        T val;
    };

    tree_node mem[N<<1];
    int tot=0;
    int root=0;

// --- helper function
    int & lc(int rt) { return mem[rt].lc; }
    int & rc(int rt) { return mem[rt].rc; }
    int get() {
        tot++;
        mem[tot].lc = mem[tot].rc = 0;
        mem[tot].val = T{}; 
        return tot;
    }

// ---- function

    PushUpType _push_up_impl;
    PushDownType _push_down_impl;

    //合并叶子
    MergeLeafType _merge_leaf;

    // push_up_impl
    // push_down_impl
// ---- function

    //构造函数
    dynamic_segment_tree(
        T,
        PushUpType push_up_impl,
        PushDownType push_down_impl,
        MergeLeafType merge_leaf

    )
        :_push_up_impl(push_up_impl),
        _push_down_impl(push_down_impl),
        _merge_leaf(merge_leaf)
    {}


    void clear() {
        tot = 0;
        root = get();
    }

    void push_up(int l,int r,int rt) {
        // int rc = mem[rt].rc;
        // int lc = mem[rt].lc;
        // mem[rt].val = std::max(mem[lc].val,mem[rc].val);
        static_assert(
                std::is_invocable_v<PushUpType,decltype(rt)> || std::is_invocable_v<PushUpType,int,int,int>,
                "need PushUpType(int rt) or PushUpType(int l,int r,int rt)"
        );
        if constexpr (std::is_invocable_v<PushUpType,decltype(rt)>) {
            _push_up_impl(rt);
        }
        else if constexpr (std::is_invocable_v<PushUpType,decltype(rt)>) {
            _push_up_impl(l,r,rt);
        }
        else {
            throw std::invalid_argument("need PushUpType(int rt) or PushUpType(int l,int r,int rt)");
        }
    }

    // rt: treenode的编号
    // pos : 目标位置
    // add : 更改的值
    // l,r,rt ,当前节点代表的[l,r]区间,和编号
    template<typename U>
    void update(int pos,const U & add,int l,int r,int rt) {
        if( l == r) {
            mem[rt].val += add; // 需要val这个值提供+=的能力
            return;
        }

        int mid = (l+r) >> 1;
        int * p = &mem[rt].lc; //得到要去的方向
        if( pos > mid ) p = &mem[rt].rc;

        if( !(*p) ) *p = get();
        update(pos,add,l,mid,*p);

        push_up(l,r,rt); // 左右孩子更新自己
    }

    //更新单个点
    // void update();

    //更新区间
    // void update();
    
    //查询,区间信息
    //[L,R] 要查询的区间
    // l,r,rt ,当前节点代表的[l,r]区间,和编号
    T query(int L,int R,int l,int r,int rt) {
        if( l >=L && r <= R) {
            return mem[rt].val;
        }

        int mid = (l+r) >> 1;
        T ret{}; // 
 
        //要查询的区间有一个部分在左边
        if( L <= mid) {
            int t = query(L,R,l,mid,mem[rt].lc);
            ret = std::max(ret,t); // 提供挑选的能力
        }

        //要查询的区间有一个部分在右边
        if( R > mid) {
            int t = query(L,R,mid+1,r,mem[rt].rc);
            ret = std::max(ret,t);
        }
        return ret;
    }


    //merge 合并两个树
    // t1,t2 -> tree1 tree2
    // l,r 合并的这个点的范围
    // 返回值 合并后新节点的编号
    int merge(int t1,int t2,int l,int r) {
        if(!t1) return t2;
        if(!t2) return t1;
        if(l == r) { //是叶子时的操作:
#ifdef DEBUG
        if( !_merge_leaf) throw std::invalid_argument("error: _merge_leaf is nullptr!");
#endif
            // mem[t1].val = _merge_leaf(mem[t1].val,mem[t2].val,l,r);
            return t1;
        }
        int mid = (l+r) >>1;
        mem[t1].lc = merge(mem[t1].lc,mem[t2].lc.l,mid);
        mem[t1].rc = merge(mem[t1].rc,mem[t2].rc.mid+1,r);
        push_up(l,r,t1);
        return t1;
    }
};

// template<
//     typename  T,
//     typename PushUpType,
//     typename PushDownType,
//     typename MergeLeafType,
//     std::size_t N = maxn>
// dynamic_segment_tree(PushUpType,PushDownType,MergeLeafType) ->dynamic_segment_tree<int,PushUpType,PushDownType,MergeLeafType>;

// template<
//     typename  T,
//     typename PushUpType,
//     typename PushDownType,
//     typename MergeLeafType,
//     std::size_t N = maxn>
// dynamic_segment_tree(T,PushUpType,PushDownType,MergeLeafType) ->dynamic_segment_tree<T,PushUpType,PushDownType,MergeLeafType,maxn>;
