Inspired by [jscheiny/Streams](https://github.com/jscheiny/Streams)

> Streams is a C++ library that provides lazy evaluation and functional-style transformations on the data, to ease the use of C++ standard library containers and algorithms. Streams support many common functional operations such as map, filter, and reduce, as well as various other useful operations such as various set operations (union, intersection, difference), partial sum, and adjacent difference, as well as many others.

使c++可以像`java8 Sreams`进行流式操作

例如:

```cpp
int arr[] = {1,2,3,4,5,6};
int arr_len  = sizeof(arr) / sizeof(a[0]);
Stream stream(arr);
int number = stream | filter([](int n){ return n % 2 == 0;}) || count();
```

设计一个库,需要先设计出来`组件`,然后`组件`互相配合形成新的`组件`或实现一个功能.
`组件`其实是对事物与功能的抽象与封装.那么`Streams`这个库的组件有哪些呢?

- `provider`,源,提供者,可以使用Iterator从中抽取数据
- `operator`,操作器,源与Fucntion的组合,利用function从上一层源中抽取数据
    - 有状态
    - 无状态
- `terminator`,终止器,也是一个操作器,只不过不能再作为源.
- `Stream`,容器,一个封装.对源的封装.



这里先不说`组件`,我们先实现一个"裸"implement,或者说平凡的implement.

```
```

我们发现上面的代码的本质就是`forwar_list`链表,表上的每一个节点都根据上个节点的迭代器获得值.
