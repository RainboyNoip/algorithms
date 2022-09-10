// 实现 adjacency list 邻接表
// BUG: auto &[v,w] : adlNode.edgesSameU(u) 如果想要修改值,可能会出错
#include "memory.hpp"
#include <concepts>

namespace rainboy {

struct adlNode {
    int v; //点
    int w; //权值
    adlNode * next = nullptr;

    operator int() const { return v;}
    operator std::tuple<int,int>() const { return {v,w};}
};

}

// Structured binging support adlNode
namespace std {
    template<>
    struct tuple_size<rainboy::adlNode> {
        static constexpr std::size_t value = 2;
    };

    template<std::size_t Index>
    struct tuple_element<Index,rainboy::adlNode> {
        using type = int;
        static_assert(Index < 2,"Index out of bounds fro rainboy::adlNode");
    };

    template<std::size_t Index>
    auto get(rainboy::adlNode & node) -> std::tuple_element_t<Index, rainboy::adlNode> &
    {
        if constexpr(Index == 0) return node.v;
        if constexpr(Index == 1) return node.w;
    }

    template<std::size_t Index>
    auto get(rainboy::adlNode && node) -> std::tuple_element_t<Index, rainboy::adlNode>
    {
        if constexpr(Index == 0) return node.v;
        if constexpr(Index == 1) return node.w;
    }

}

namespace rainboy {

    using std::tuple_size;
    using std::tuple_element;
    using std::tuple_element_t;
    using std::get;
    
class adjacencyList {
public:
    using allocator_type = std::pmr::polymorphic_allocator<adlNode>;

private:
    std::pmr::vector<adlNode*> m_head; // 
    std::size_t m_count;
    std::size_t lowerBound{1};
    allocator_type alloc;

public:
    explicit adjacencyList(std::size_t nodeCount, const allocator_type & alloc = {})
        : m_count(nodeCount),m_head{nodeCount+1,alloc.resource()},alloc(alloc)
    {}

    virtual ~adjacencyList() {
        //TODO: 如果使用的 是 std::pmr::monotonic_buffer_resource 就deallocate 节省时间?
        
#if defined (EXTREMELY_OPTIMAL)
        for(auto & it : m_head){
            adlNode * t = it;
            while( t != nullptr){
                adlNode * tmp = t;
                t = t->next;
                alloc.deallocate(tmp, 1);
            }
        }
#endif

    }

    void addEdge(int u,int v,int w = 0){
        adlNode *p = alloc.allocate(1);
        p->next = m_head[u];
        p->v = v;
        m_head[u] = p;
    }

    void addEdge2(int u,int v,int w = 0){
        addEdge2(u,v,w);
        addEdge2(v,u,w);
    }

    bool edgeExist(int u,int v){
        return findEdge(u, v) != nullptr;
    }

    adlNode * findEdge(int u,int v) const {
        if(u > m_count || u < lowerBound) return nullptr;
        for(adlNode * it = m_head[u]; it != nullptr ; it = it->next){
            if( it->v == v ) return it;
        }
        return nullptr;
    }

    struct Iterator{
        using iterator_category = std::forward_iterator_tag ;
        using value_type = adlNode;
        using pointer = value_type *;
        using reference = value_type&;
        using difference_type = std::ptrdiff_t;
        reference operator*() { return *m_p;}
        const Iterator& operator++(){
            if( m_p != nullptr)
                m_p = m_p->next;
            return *this;
        }

        Iterator operator++(int) {
            Iterator tmp = *this;
            if( m_p != nullptr)
                m_p = m_p->next;
            return tmp;
        }

        bool operator==(const Iterator & other) const { return m_p == other.m_p; }

        adlNode * m_p;
    };

    struct edgesSameU {
        adlNode * _head;
        Iterator begin() { return {_head};}
        Iterator begin() const{ return {_head};}
        constexpr Iterator end() const {return {nullptr};}
    };

    edgesSameU sameVertexEdges(int u){
        return {m_head[u]};
    }

    // auto begin() ;
    // auto begin() const;
    // auto end();
    // auto end() const;
};

} // end namespace rainboy
