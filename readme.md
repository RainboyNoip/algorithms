# Algorithms

<p align="center">
    <a alt="c++">
        <img src="https://img.shields.io/badge/c++-%2300599C.svg?style=for-the-badge&logo=c%2B%2B&logoColor=white" /></a>
    <a href="https://www.gnu.org/licenses/gpl-3.0" alt="gpl-3.0">
        <img src="https://img.shields.io/github/license/rainboyNoip/algorithms?style=for-the-badge&color=blue" /></a>
    <a href="https://github.com/RainboyNoip/algorithms" alt="gpl-3.0">
        <img src="https://img.shields.io/badge/version-Alpha-blue?style=for-the-badge" /></a>
</p>


- [Algorithms](#algorithms)
  - [目的](#目的)
  - [约定](#约定)
  - [安装与更新](#安装与更新)
  - [文档](#文档)
  - [vim 自动补全](#vim-自动补全)
    - [0. 安装方法](#0-安装方法)
    - [1. 单独使用,不依赖其它vim插件](#1-单独使用不依赖其它vim插件)
    - [2. 配合coc.nvim使用,更好的使用体验](#2-配合cocnvim使用更好的使用体验)
  - [UtilSnips 补全](#utilsnips-补全)
  - [作为neovim的插件](#作为neovim的插件)
  - [更新日志](#更新日志)
  - [TanksFor](#tanksfor)

<small><i><a href='http://ecotrust-canada.github.io/markdown-toc/'>Table of contents generated with markdown-toc</a></i></small>

## 目的

<!-- 受[xtaci/algorithms: Algorithms & Data structures in C++.](https://github.com/xtaci/algorithms) 启发，把写题目用到的算法与数据结构写出来，用于：-->

1. 快速写题目。
2. 个人算法总结
3. 算法学习

## 约定

1. 一个算法用一个`.hpp`文件表示放到include下. ( one .header file per algorithm. )
2. 算法演示的demo程序放到src下.  ( one demo per algorithm.  )
3. TAB = 4 space.  set ts=4 in vim
4. Graph的输出格式为 [Graphviz](http://www.graphviz.org/) Dot格式.  (the output format of the graph is in dot of graphviz.)
5. 易用 easy to use
6. 代码即文档： 只需要看代码(或代码注释)就可以学会如何使用
7. 头文件提供源码：只用包含头文件即可使用

## 安装与更新

```bash
# 下载本仓库到
g++ clone https://github.com/RainboyNoip/algorithms ~/.algorithms
vim ~/.zshrc # 这个由你使用的终端来决定

# 手动添加如下
# 修改默认g++ 查询include的路径
export CPLUS_INCLUDE_PATH=$HOME/.algorithms:$CPLUS_INCLUDE_PATH
## 为了使用algorithms 下的工具
export PATH=$PATH:$HOME/.algorithms/bin
```

其它依赖软件

```bash
# 安装graphviz,xsel
sudo apt install graphviz xsel
```


bin目录下的工具有 TODO
```plaintext
bin
├── b               编译当前目录下字典序最小的cpp文件，并自动` < in`,具体查看`b --help`
├── dot2png.py
├── dp.py
├── in2dot
├── lsoitools
├── oi-show.py
├── randint.py
├── r_test.js
└── tran2one.py 如果你的代码文件中包含了本库中hpp文件,会把你写的代码和本库中的hpp文件拼接,转换成一个文件,方便提交到oj

```

## 文档

1. 先看`examples/`的代码
2. 再看对应的源代码，代码即文档

功能分类

每个源文件都有使用方法的说明

- [基础零件](./include/base)
  - [fastIO 快速输入输出](./include/base/fastIO.hpp) `fastIO.hpp`
  - [抽取器 `yank_adaptor.hpp`](./include/base/yank_adaptor.hpp) 从左容器抽取数据到右窗口
  - [常用宏 `macro.hpp`](./include/base/marco.hpp)
    - `af(i,n)`,`ff(i,n)`
- [碎片代码 `chips`](./include/chips/)
  - [`inf.hpp' 正负inf](./include/chips/inf.hpp)
  - [`multi_cout.hpp' 一次输出多个数据](./include/chips/)
  - [`range.hpp' 类似python的range,给for使用](./include/chips/range.hpp)
  - [`relative_pos.hpp' 相对位置](./include/chips/relative_pos.hpp)
  - [`ring2chain.hpp' 拆环成链](./include/chips/ring2chain.hpp)
  - [`upd_max.hpp' 更新最大值](./include/chips/upd_max.hpp)
- [常用算法](./include/algo)
  - [二分查找](./include/algo/binary_search.hpp) `algorithms/binary_search.hpp`
  - [离散化 discrete](./include/algo/discrete.hpp)
  - [排列组合 combination](./include/algo/combination.hpp)
    - 全组合,全排列,
    - 组合(n个选m个),GospersHack算法
    - 子集生成
  - [倍增算法 double](./include/algo/double.hpp)
    - `multi_doule<> crtp 子类`,rmq
- [数据结构](./include/data_structure)
  - [`bit.hpp`](./include/data_structure/bit.hpp) 二进制集合操作
  - [`pre_sum` 前缀和](./include/data_structure/pre_sum.hpp)
  - [`sub_array` 差分数组](./include/data_structure/sub_array.hpp) 多次区间增减,一次查询单点 
  - [`binary_heap` 堆](./include/data_structure/binary_heap.hpp) 动态排序,`log(n)`
  - [bit 树状数组](./include/data_structure/bit.hpp) 
     单点修改{区间和,区间最值},逆序对,
     区间修改{单点值(动态查询差分数组),区间和}
- [图](./include/graph)
  - [linkList.hpp 链式向量星,图的基本存储](./include/graph/linkList.hpp)
  - [edgeArray.hpp 边集数组](./include/graph/edgeArray.hpp)
  - [`bipartile_graph_color` 二分图染色,无奇环判定](./include/graph/bipartile_graph_color.hpp)
  - [`tarjan_scc` 强连通分量](./include/graph/tarjan_scc.hpp)
  - [`heavy_light_decomposition` 树轻重划分](./include/graph/heavy_light_decomposition.hpp)
  - [`lca_craw` 爬树(倍增)法求lca](./include/graph/lca_craw.hpp)
  - [`lca_craw` 爬树(倍增)法求lca](./include/graph/lca_craw.hpp)
  - [`dsu_on_tree` 树上启发发式合并 模板](./template/dsu_on_tree.txt)
- [工具](./include/utils)
  - [输出调试](./include/utils/log.hpp) `utils/log.hpp`
  - [输出调试](./include/utils/debug.hpp) `utils/debug.hpp`
  - [输出调试](./include/utils/dbg.h) `utils/dbg.h` 👉 [使用方法](https://github.com/sharkdp/dbg-macro)
  - [随机数生成] TODO
  - [table](./include/utils/table.hpp) `utils/table.hpp` 把数据按表格的形式输出,通常用于调试
  - [输出调试:log](./include/utils/log.hpp) `utils/log.hpp` 一种带guard的输出调试
  - [graphviz](./include/utils/graphviz.hpp) `utils/graphviz.hpp` 生成graphviz dot图,[graphviz官方文档](https://graphviz.org/documentation/)
  - [程序调用 subprocess](./include/utils/subprocess.hpp) `utils/subprocess.hpp` 实现类似于python的popen函数,用于c++调用其它的程序

## vim 自动补全

### 0. 安装方法

### 1. 单独使用,不依赖其它vim插件

如果你没有使用任何vim的插件,例如noilinux2.0下的纯vim不安装插件

安装方法TODO

### 2. 配合coc.nvim使用,更好的使用体验

原理: [Create custom source · neoclide/coc.nvim Wiki](https://github.com/neoclide/coc.nvim/wiki/Create-custom-source)

1. 先安装[coc.nvim](https://github.com/neoclide/coc.nvim/)
2. 使用`vim-plug`或`packer.nvim`管理当前库,例如,
  ```
  use 'RainboyNoip/algorithms'
  ```
3. 打开一个cpp文件:`vim 1.cpp`
4. 输入`tarja`,然后回车补全

## UtilSnips 补全

在[UtilSnips](./UltiSnips)目录下放置了我常用代码片断,vim中如何安装`UltiSnips`,请自行搜索

```vimL
let g:global_author = '<you name>'
let g:global_email = '<your email>'
```

[snippets使用文档](./snips.md)

## 作为neovim的插件

本项目可以作为neovim的插件

依赖:

- [lazy.nvim](https://github.com/folke/lazy.nvim)
- [snacks.nvim](https://github.com/folke/snacks.nvim)


```lua
return  {
  'RainboyNoip/algorithms'
  lazy = true,
  dependencies = { "folke/snacks.nvim" },
  config = function() {
    -- todo
  }
}
```

## 更新日志

[更新日志](./log.md)

## TanksFor

- [GitHub - sharkdp/dbg-macro: A dbg(…) macro for C++](htps://github.com/sharkdp/dbg-macro)
- [agauniyal/rang: A Minimal, Header only Modern c++ library for terminal goodies 💄✨](https://github.com/agauniyal/rang)
- [arun11299/cpp-subprocess: Subprocessing with modern C++](https://github.com/arun11299/cpp-subprocess)
