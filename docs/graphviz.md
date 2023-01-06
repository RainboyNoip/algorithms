# graphviz.hpp 使用手册

需要c++20

为了方便调试图与树的相关代码,对dot语言进行了简单的封装,**通过代码,创建dot文件**,具有
以下的功能:

- 创建有向图,无向图
- 设置全局的属性,包括边,点,图
- 图中添加一个点(node)
- 改变点属性
- 将图转变成`dot`文件或`png`文件

[源码在`../include/utils/graphviz.hpp`](../include/utils/graphviz.hpp),单头文件


你需要下载 [GraphViz](http://www.graphviz.org),graphviz的使用可以查看教程[dot guide](https://graphviz.org/pdf/dotguide.pdf)

## quick tutorial

```cpp
#include <iostream>
#include "utils/graphviz.hpp"
using namespace DOT;
int main(){

    //创建一个有向图,默认的名字叫做1
    auto g = graphviz<DI>(); 

    //设定全局 边的属性
    g.setEdgeAttributes<DOT::dot_attrs::color>(dot_color::red); 

    auto & n1 = g.addNode(1); //添加一个点,编号1
    auto & n2 = g.addNode(2); //添加一个点,编号1
    n1.set<dot_attrs::color>(dot_color::red); //点的颜色
    n2.set<dot_attrs::color>(dot_color::blue);//点的颜色

    g.addEdge(n1, n2);//创建一条边

    //输出 转成 dot script 的字符串
    std::cout << g.to_dot() << std::endl; 

    //输出成图片 1.png
    g.output();

    return 0;
}
```

## API

### 1. graph

- 创建一个图

```cpp

using namespace DOT;

graphviz<> mygrah1; //创建了一个无向图
graphviz<> mygrah2("mygraph_id"); //创建了一个无向图,id 为 mygraph_id

//创建了一个有向图,id 为 direct_id
graphviz<DI> mygraph2("direct_id") ;
```

API

- `set<dot_attrs::*>(val)` 设置图的属性
- `setNodeAttributes<dot_attrs::*>(val)` 设置全局点的属性
- `setEdgeAttributes<dot_attrs::*>(val)` 设置全局边的属性

- `dot_edge & addEdge(size_t n1,size_t n2)`,在图上创建一边条边,边上的两点为n1,n2
- `dot_edge & addEdge(size_t n1,dot_node & n2)`,在图上创建一边条边,只不过有一个是`dot_node`类型
- `dot_edge & addEdge(doe_node &n1,size_t n2)`,同上
- `dot_edge & addEdge(doe_node &n1,dot_node & n2)`,同上


添加点
- `dot_node & addNode(std::size_t id)`,添加一个点,并有一个整数的id
- `dot_node & addNode(std::size_t idx,std::string_view name)`

- `edgeCount()` 得到边的数量

- `string to_dot()`,转成`dot`的字符串
- `void ouput()`,输出`tmp.dot`并创建对应的`png`,png名字为图的id


### 2. attributes

分类

```cpp
enum class dot_attrs {
    color,      //ENC dot_color
    label       //ENGC std::string
};
```

设置属性:

```cpp
// 创建一个node,id为1
DOT::dot_node mynode(1);

//设置color 为蓝色
mynode.set<DOT::dot_attrs::color>(DOT::dot_color::blue);
//最后输出: 1[color="blue"]


//设置label
mynode.set<DOT::dot_attrs::label>("foo")
//最后输出: 1[label="foo"]

```

`dot_color`有哪些颜色呢?
```plaintext
enum class dot_color : int {
    blue,
    red,
    gray,
    white,
    black
};
```

### 3. node

### 4. edge

## 其它

- [gvgen](http://www.graphviz.org/pdf/gvgen.1.pdf)
