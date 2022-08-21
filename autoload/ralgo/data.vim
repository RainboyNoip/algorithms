let s:header_seq = ['base.hpp','graph/edgeArray.hpp','graph/linkList.hpp','graph/tarjan_scc.hpp','graph/bipartile_graph_color.hpp','algorithms/binary_search.hpp']

let s:word_pairs = { 
    \'binary_search': { 
        \'header': 'algorithms/binary_search.hpp', 
        \'expand': 'binary_search(Iter first,Iter last,Compare Func)', 
    \},
    \'bipartite_graph_color': { 
        \'header': 'graph/bipartile_graph_color.hpp', 
        \'expand': 'bipartite_graph_color<MAXN::value,linkList> bp_gcolor;', 
    \},
    \'linkList': { 
        \'header': 'graph/linkList.hpp', 
        \'expand': 'linkList<MaxN> e;', 
    \},
    \'edgeArray': { 
        \'header': 'graph/edgeArray.hpp', 
        \'expand': 'edgeArray<MAXN::value,MAXE::value> ea;', 
    \},
    \'tarjan_scc': { 
        \'header': 'graph/tarjan_scc.hpp', 
        \'expand': 'tarjan_scc<MAXN::value,linkList> scc;', 
    \},
\}

let s:complete_items = [
    \{
        \'word': 'binary_search', 
        \'info': '二分查找', 
    \},
    \{
        \'word': 'bipartite_graph_color', 
        \'info': '二分图染色', 
    \},
    \{
        \'word': 'linkList', 
        \'info': '链式前向星,存图', 
    \},
    \{
        \'word': 'edgeArray', 
        \'info': '边集数组', 
    \},
    \{
        \'word': 'tarjan_scc', 
        \'info': 'tarjan求强连通分量', 
    \},
\]


function! ralgo#data#GetComplete() 
    return s:complete_items
endfunction

function! ralgo#data#GetHeader() 
    return s:header_seq
endfunction

function! ralgo#data#GetWordPairs() 
    return s:word_pairs
endfunction
