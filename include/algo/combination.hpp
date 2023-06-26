#include "base.hpp"
/**
 * 
 * 排列 std::next_pemutation
 * 组合
 *  - 所有的可能的组合 选1个,选2个,选3个 ..... 选n个
 *   - 递归实现
 *   - 二进制实现
 *  - 选m个的所有组合
 *   - 递归实现
 *   - 二进制实现
 *
 * GeospersHack 的使用
 *  for(auto i : g ) {
 *      for( auto j : number_to_choose_arr(i) ){
 *          cout << j << " ";
 *      }
 *      cout << "\n";
 * }
 *
 * std::next_pemutation
 */

// 全组合，从n个进而选1个，2个，3个.... n个

struct full_combanation{
    std::vector<int> choose;
    std::function<void(std::vector<int>&)> func;
    int n;
    
    void dfs_choose(int x) {
        if(x == n+1) { //选完了
            func(choose);
        }
        
        dfs_choose(x+1); //不选
        choose.push_back(x);
        dfs_choose(x+1);//选
        choose.pop_back(x);
    }

    void work(int n_){
        n= n_;
        choose.clear();
        dfs_choose(1);
        

    }
};

//dfs 实现从n个里选m个

void dfs_n_choose_m(int x)
{
    if( choose.size() > m ) {

        return;
    }
    //边界2, 剩下的全选也不夠
    if( choose.size() + (n-x+1) < m )
    {
        return;
    }

}


//从n里选m个所有可以的二进制表示

struct GeospersHack {
    int n_;
    int m_;

    explicit
    GeospersHack(int n,int m) 
    :n_(n),m_(m)
    {}

    static int next_combination(int m) {
        int lb = m & -m; //保留最低位置的1
        int sum = m + lb; //使最低连续的1进位
        int Xor = sum ^ m; //只保留最低连续1和进位的1
        return (Xor >> (__builtin_ctz(lb) +2) ) | sum;
    }

    struct Iterator {
        int v_;
        Iterator(int V) : v_(V) {}

        Iterator operator++() {
            v_ = next_combination(v_);
            return *this;
        }

        int operator*() const {
            return v_;
        }

        bool operator!=(const Iterator &oth) const {
            return v_ < oth.v_;
        }
    };

    Iterator begin() const  {
        return {(1<<m_) -1};
    }

    Iterator end() const  {
        return  {(1<<n_) -1};
    }
};


//数字转成对应的选的数的array
//和上面GeospersHack 配合使用
// i.e : 7 -> 0b0111 -> {1,2,3}
struct  number_to_choose_arr {
    int n_;

    number_to_choose_arr(int n) :n_(n) { }
    number_to_choose_arr(const GeospersHack::Iterator & it) :n_(it.v_) { }

    struct Iterator {
        int n_;
        int idx;
        Iterator(int n) : n_(n),idx(0) {
            if(n_ != 0 ) {
                count_idx();
            }
        }
        inline void count_idx() {
                int cnt = __builtin_ctz(n_);
                idx+=cnt;
                n_>>=cnt; //去除末尾的0和最后一个1
        }

        Iterator operator++() {
            if(n_ == 0 ) 
                return *this;
            n_>>=1; //去除末尾的1
            ++idx;
            count_idx();
            return *this;
        }

        int operator*() const {
            return idx+1;
        }

        bool operator != (const Iterator & oth ) {
            return n_ != oth.n_;
        }
    };

    Iterator begin() const {
        return {n_};
    }

    Iterator end() const {
        return {0};
    }

};

void combination_baseOn_next_permutation(int n ,int m)
{

    std::vector<int> v;
    for(int i =1;i<=n-m;i ++ )
        v.push_back(0);
    for(int i =1;i<=m;i++)
        v.push_back(1);

    do {
        for(int i = 0 ;i< v.size() ;i++ ){
            if( v[i] == 1 ) {
                //第i/i+1 个被选了
            }
        }
        //for(auto i : v) {
        //    cout << i << " ";
        //}
        //cout << "\n";

    }while(std::next_permutation(v.begin(),v.end()));
}
