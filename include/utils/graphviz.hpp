/*  Interface to the [GraphViz graphing](http://www.graphviz.org/content/dot-language) tool */
#pragma one
#include <string>
#include <map>
#include <iostream>
#include <fstream>
#include <string_view>
#include <unordered_map>
#include <list>
#include <filesystem>


namespace DOT {

namespace fs = std::filesystem;

// =======================> 工具函数 与工具类
namespace dot_utils {

    //给字符串添加包围的字符 abc -> "abc"
    std::string quoted(const std::string & quoted,char quote){
        return quote + quoted + quote;
    }

    //作用: 把 enum 的值 转成对应的 string_view
    template<auto... t>
    constexpr auto get_enumerator_names_impl(){
        auto a = std::string_view {
            __PRETTY_FUNCTION__,
                sizeof(__PRETTY_FUNCTION__)-3
        };
        a.remove_prefix(62);
        return a;
    }

    template <typename Enum, auto...vs>
    constexpr auto get_enumerator_names(std::index_sequence<vs...>) {
        return get_enumerator_names_impl<static_cast<Enum>(vs)...>();
    }

    template<typename Enum>
    constexpr std::size_t get_enum_class_name_size() {
        constexpr std::string_view name {__PRETTY_FUNCTION__};
        //std::cout << name << std::endl;
        std::size_t start;
        //先找到 = 
        for(int i = 0;i< name.size() ;i++) {
            if( name[i] == '=') {
                start = i+2;
            }
            else if (name[i] == ';')
                return i-start;
        }
        return 0;
    }

    template<typename T>
    std::string_view enum_name(T t){

        constexpr auto enum_class_name_offset
            = get_enum_class_name_size<std::decay_t<T>>()+2;
        // +2 -> :: 
        // Fruit::  sizeof(Fruit) = 5
        // 略过的长度 5+2
        //std::cout << "offset" << std::endl;
        //std::cout << 
            //enum_class_name_offset
            //<< std::endl;
        constexpr auto names = get_enumerator_names<T>(std::make_index_sequence<10>{});
        //std::cout << names << std::endl;
        // 第一个 { 位置
        int index = static_cast<int>(t); // 得到 enum 的位置 , 0 ,1 ,2 ,3,4
        std::size_t start = 0,end = names.size();
        int cnt = 0;
        for(int i = 0 ;i < names.size();){
            if( names[i] == ' ' && names[i+1] == '{' && start == 0){
                start = (i+2);
                i+=2;
            }
            else if( names[i] == ',' && names[i+1] == ' '){ //一个分割符号
                cnt++;
                if( cnt == index ){
                    start = (i+2);
                }
                else if( cnt == index+1) {
                    end = i;
                    break;
                }
                i+=2;
            }
            else ++i;
        }
        start += enum_class_name_offset;
        return std::string_view{
            names.begin() + start,
                end - start
        };
    }

} // end namespace dot_utils
    
enum class graphviz_type {
    graph,      //无向图
    digraph,    //有向图
};

//有向图,无向图的 全局值
auto constexpr GRAPH = graphviz_type::graph;
auto constexpr DIGRAPH = graphviz_type::digraph;
auto constexpr UNDI= graphviz_type::graph;
auto constexpr DI = graphviz_type::digraph;
auto constexpr UNDIRECT = graphviz_type::graph;
auto constexpr DIRECT = graphviz_type::digraph;


enum class gType : int {
  edge, // 边
  node, // 点
  graph,// 图
  cluster // 子图
};

constexpr auto E = gType::edge;
constexpr auto N = gType::node;
constexpr auto G = gType::graph;
constexpr auto C = gType::cluster;

//颜色
enum class dot_color : int {
    blue,
    red,
    gray,
    white,
    black
};

enum class dot_style : int{
    filled
};


enum class dot_attrs {
    color,      //ENC dot_color
    label       //ENGC std::string
};

// 是否是gType, E N G C 中的一种
template<typename ... U>
    requires (std::same_as<U, gType> && ...) && (sizeof...(U) > 0)
constexpr bool anyofGtype(gType First,U... type){
    //static_assert(sizeof...(type) > 0,"sizeof args must >=2" );
    return ( (First == type) || ...);
}

//是否是 dot 的属性,color, label 中的一种
template<typename ... U>
    requires (std::same_as<U, dot_attrs> && ...) && (sizeof...(U) > 0)
constexpr bool anyofDotAttr(dot_attrs First,U... type){
    //static_assert(sizeof...(type) > 0,"sizeof args must >=2" );
    return ( (First == type) || ...);
}

// -----------> value -> string
template<typename ValueType> requires std::same_as<ValueType, dot_color>
std::string to_string(ValueType && val){
    // enum 转字符串
    return std::string(dot_utils::enum_name(val));
}

template<typename ValueType> requires std::convertible_to<ValueType, std::string>
std::string to_string(ValueType && val){
    return std::forward<ValueType>(val);
}

template<typename ValueType> requires std::integral<ValueType>
std::string to_string(ValueType && val){
    return std::to_string(val);
}

//字符 转字符串
template<typename ValueType>
    requires std::same_as<std::decay_t<ValueType>, char>
std::string to_string(ValueType && val){
    //TODO 这里要改成 quoteMe
    return std::string(1,val);
}
// -----------> value -> string -- END

// 检查 
template<gType type,dot_attrs attr,typename ValueType>
constexpr bool validate_attr(){
    using enum dot_attrs;
    switch(attr) {
        //如果 attr 是 color ,那么 只能用在E N C,且只能是dot_color 中的一种
        case color: return anyofGtype(type,E,N,C) && std::is_same_v<ValueType, dot_color>;
        // attr ,label 只能用在 ENGC ,且值能转换string
        case label: return anyofGtype(type,E,N,G,C); // TODO 约束 可以执行to_string && { }
    }
    return 0;
}

//是否把属性转成字符串 带有quote
// attr 是color可以 quoted_types
constexpr bool quoted_types(dot_attrs attr){
    using enum dot_attrs;
    return anyofDotAttr(attr, color,label);
}

// quote 一个字符串
std::string quoteMe(dot_attrs attr,const std::string & value){
    // 是感叹号开头 用 < >
    if( value.length() > 0 && value[0] == '!'){ // TODO ???
        return '<' + value.substr(1) +'>';
    }
    if( quoted_types(attr) )
        return dot_utils::quoted(value, '"');
    return value;
}


// =======================> 工具函数 与工具类

// 存属性的容器
template<gType type>
class dot_attributes {
private:
    std::unordered_map<dot_attrs,std::string> attrs;
public:

    template<dot_attrs attr,typename U>
        requires (validate_attr<type, attr, U>())
    void set(U&& value){
        attrs[attr] = to_string(std::forward<U>(value));
    }

    //attr的数量
    std::size_t size() const { return attrs.size(); }

    //to_dot
    std::string to_dot() const{
        std::string attrsOuput{};
        bool first = true;
        if( this->size() > 0 ) {
            attrsOuput += "[";
            for (const auto& [attr,val] : attrs) {
                std::string name { dot_utils::enum_name(attr) };
                attrsOuput +=  (first ? "" : " ,") + name + " =" + quoteMe(attr, val);
                first = false;
            }
            attrsOuput += "]";
        }
        return  attrsOuput;
    }

};

struct dot_edge;

//结点的属性
struct dot_node {
private:
    std::size_t id;
    dot_attributes<N> m_attr;
public:
    friend dot_edge;
    //std::string name;
    dot_node() = delete;
    dot_node(std::size_t id) :id{id} 
    {}

    //设置属性
    template<dot_attrs attr,typename ValueType>
    void set(ValueType&& val) {
        m_attr.set<attr>( std::forward<ValueType>(val) );
    }

    // 整个结点转换成 string
    std::string to_dot() const {
        std::string nodeOutput{};
        nodeOutput += dot_utils::quoted(std::to_string(id) ,'"') + m_attr.to_dot();
        return nodeOutput;
    }
};


//边的描述
struct dot_edge {
    dot_node& nodeOne;
    dot_node& nodeTwo;
    dot_attributes<E> m_attr;

    dot_edge() = delete;
    dot_edge(dot_node & n1 ,dot_node & n2)
        : nodeOne{n1},nodeTwo{n2}
    {}
    
    template<dot_attrs attr,typename ValueType>
    void set(ValueType&& val) {
        m_attr.set<attr>( std::forward<ValueType>(val) );
    }

    template<graphviz_type type>
    std::string to_dot() const {
        std::string edgeLink = "--";
        if constexpr (type == graphviz_type::digraph)
            edgeLink[1] = '>';

        std::string edgeOutput{};

        edgeOutput += "  " + dot_utils::quoted(std::to_string(this->nodeOne.id) ,'"') 
            + ' ' + edgeLink + ' '
            + dot_utils::quoted(std::to_string(this->nodeTwo.id), '"')
            + m_attr.to_dot();
        return edgeOutput;
    }
};



//默认是无向图
template<graphviz_type Direction = UNDIRECT>
class graphviz {

private:

    fs::path graphviz_path = "/usr/bin/dot";
    // std::unordered_map<std::size_t, dot_node> nodes; //存点

    // 为什么不用unordered_map , unordered_map 输出的时候,从大到小
    // map 从小到大
    std::map<std::size_t, dot_node> nodes; //存点

    std::list<dot_edge> edges; //存边
                               //
    dot_attributes<G> graph_attr;
    //dot_attributes<C> graph_attr; TODO 子图
    dot_attributes<N> g_node_attr; //global node attr
    dot_attributes<E> g_edge_attr; //global edge attr
    std::string id{"1"};
    //this.use = dot dot 布局
public:

    graphviz() = default;
    graphviz(std::string_view id) : id{id} {}

    //添加一个点
    dot_node & addNode(std::size_t idx){
        if( !hasNode(idx) ){ //没有找到就创建
            nodes.emplace(idx,idx);
        }
        return nodes.find(idx)->second;
    }

    //是否有点
    bool hasNode(std::size_t idx){
        if( nodes.find(idx) == nodes.end())
            return false;
        return true;
    }

    //添加一个点
    dot_node & addNode(std::size_t idx,std::string_view name){
    }

    //添加一个点
    dot_node & addNode(std::size_t idx,std::string&& name){
    }

    //删除一个点
    template<typename U>
        requires std::same_as<U, std::size_t> || std::same_as<U, dot_node>
    void removeNode(U&& n,bool force_remove_edge = true){
    }

    std::size_t nodeCount() const {
        return nodes.size();
    }

    //==== 添加边
    dot_edge & addEdge(std::size_t n1,std::size_t n2){
    }

    template<typename Node>
        requires std::same_as<Node, dot_node>
    dot_edge & addEdge(std::size_t n1,Node&& n2){
    }

    template<typename Node>
        requires std::same_as<std::decay_t<Node>, dot_node>
    dot_edge & addEdge(Node&& n1,std::size_t n2){
        edges.emplace_back(n1,addNode(n2));
    }

    //template<typename Node>
        //requires std::same_as<Node, dot_node>
    dot_edge & addEdge(dot_node& n1,dot_node& n2){
        edges.emplace_back(n1,n2);
    }

    std::size_t edgeCount() const {
        return edges.size();
    }


    //得到全局边的属性
    //auto & getEdgeAttributes()
    //==== 添加边结束
    
    //设置 图的属性
    template<dot_attrs attr,typename ValueType>
    void set(ValueType&& val) {
        graph_attr.set<attr>( std::forward<ValueType>(val) );
    }

    //设置 全局node的属性
    template<dot_attrs attr,typename ValueType>
    void setNodeAttributes(ValueType&& val) {
        g_node_attr.set<attr>( std::forward<ValueType>(val) );
    }

    //设置 全局edge的属性
    template<dot_attrs attr,typename ValueType>
    void setEdgeAttributes(ValueType&& val) {
        g_edge_attr.set<attr>( std::forward<ValueType>(val) );
    }

    //输出
    //void output(fs::path & output_path){
    void output(){
        // 创建一个内存的文件,使用dup2 重定向
        // 使用fork 创建一个分支
        // dup2
        // https://linux.die.net/man/3/open_memstream       
        
        std::string filename = "tmp.dot";
        std::fstream file(filename,file.out | file.trunc);
        if( !file.is_open()){
            std::cout << "failed to write dot file : " << filename << std::endl;
            return;
        }
        file << this->to_dot();
        file.close();

        //simply impletion
        std::string cmd{graphviz_path.string()};
        cmd += " -Tpng";
        cmd += " -o " + this->id +".png";
        cmd += " tmp.dot";
        std::system(cmd.c_str());
    }

    //转成dot语言
    std::string to_dot(){
        std::string dotScript{ dot_utils::enum_name(Direction) };
        dotScript += ( " \"" + id + "\" {\n");

        //graph attributes
        if( graph_attr.size() > 0)
            dotScript += "  graph" + graph_attr.to_dot() + ";\n";
        //node attributes
        if( g_node_attr.size() > 0)
            dotScript += "  node" + g_node_attr.to_dot() + ";\n";
        //edge attributes
        if( g_edge_attr.size() > 0)
            dotScript += "  edge" + g_edge_attr.to_dot() + ";\n";

        //eachs nodes
        for (const auto& n : nodes) {
            dotScript += "  " + n.second.to_dot() + ";\n";
        }

        //eachs edges
        for (const auto& e : edges) {
            dotScript += "  " + e.to_dot<Direction>() + ";\n";
        }

        dotScript += "}\n";

        return dotScript;
    }
};

} // end namespace DOT

