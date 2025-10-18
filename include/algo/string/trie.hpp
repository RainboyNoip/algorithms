//字典树Trie
// 创建: Trie mytr;
// 插入字符串: mytr.insert(s[],100);
// jsra字符串: mytr.find(s[],100);
#include "base/macro.hpp"

template<std::size_t SIZE = maxn>
struct Trie
{

    struct node {
        int ch[2]; //孩子编号
        int end; //当前点是否是一个结点
    };
    node nodes[SIZE];
    int tot=0;

    Trie() : tot{0} {}

    void clear() {
        memset(nodes,0,sizeof(nodes));
        tot=0;
    }
    int & ch(int cur,int v) {
        return nodes[cur].ch[v];
    }

    //cur节点的v孩子是否存在
    inline bool exist(int cur,int v) {
        return ch(cur,v) != 0;
    }

    //在cur这个结点下面添加一个点
    //并返回孩子cur的v孩子的编号
    int push(int cur,int v) {
        if( !exist(cur,v) ) ch(cur,v) = ++tot; //创始新的
        return ch(cur,v); //返回这个孩子的编号
    }

    // 插入一个字符串
    void insert(char* str,int len)
    {
        int cur = 0;
        for (int k = 0; k < len; ++k) //遍历每一个字符
            cur = push(cur,str[k]-'a');
        nodes[cur].end++;
    }


    //查找一个字符串
    int find(char* str,int len)
    {
        int cur = 0;
        for (int k = 0; k < len; k ++ )
        {
            int v = str[k] - 'a';
            if( exist(cur,v) ) //孩子存在表明边存在
                cur = ch(cur,v);
            else return false;
        }
        return nodes[cur].end; //当前结点,是否是终点
    }
};

