# graphviz.hpp 使用手册

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

### 2. attributes

### 3. node

### 4. edge

## 其它

- [gvgen](http://www.graphviz.org/pdf/gvgen.1.pdf)
