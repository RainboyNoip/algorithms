" 加入dict
" <c-r>=complete()
" 执行过程:
" 1. popmenu 提示触发
" 2. expand 触发
" 3. 自动加入对应的头文件

set completeopt=menu,menuone,noinsert
let g:algorimth_dir = '/home/rainboy/mycode/RainboyNoip/algorithms/include/'


"数据
let g:algo_data = {
    \ "linkList" : {
        \ "header" : ["graph/linkList.hpp"],
        \ "preview" :"graph/linkList.hpp",
        \ "word" : 'linkList',
        \ "abbr" : 'linkList<100> e;'
        \},
    \ "edgeArray" : {
        \ "header" : ["graph/edgeArray.hpp"],
        \ "preview" :"graph/edgeArray.hpp",
        \ "word" : 'edgeArray',
        \ "abbr" : 'edgeArray<100> ea'
    \}
\}

" 头文件的顺序,用于确定添加头文件的位置
let s:header_seq = [
    \ 'base.hpp',
    \ 'graph/linkList.hpp'
    \ ]

function! GetCodePreivew(name)
    return join(readfile(g:algorimth_dir .. a:name),'\n')
endfunc

function! GetCodeContentList(name)
    return  readfile(g:algorimth_dir .. a:name)
endfunc

" 传一个文件,返回需要的头文件列表
" arg content_list
function! GetHeaderList(content_list)
    "let l:headers  = filter(readfile( g:algorimth_dir .. a:filename), 'v:val =~ "^#include\s*\"\S\+\"\s*$"')
    let l:headers  = filter(a:content_list, 'v:val =~? "^#include\\s\*\"\\S\\+\"\\s\*$"')
    "echo l:headers
    return map(l:headers,'matchstr(v:val,"#include\\s\*\\zs\\S\\+\\ze\\s\*")')
endfunc

"echo GetHeaderList(GetCodeContentList('graph/linkList.hpp'))

" 参数,需要加入的头文件
" 返回: 需要添的传这的个头文件在当前buffer的行范围
" 返回值 [start,end]
" 
function! MatchHeaderInfo(header_name)
    "let lc = getline('$') " line count
    let l:self_index = index(s:header_seq,a:header_name)
    "echo l:self_index
    let l:ret = 1
    for i in range(1,getline('$'))
        let l:line  = getline(i)
        if l:line =~? '^#include\s*<\S\+>\s*$'
            let l:ret = i + 1" 下一行
        elseif l:line =~? '^#include\s*"\S\+"\s*$'
            let l:inc = matchstr(l:line,'^#include\s*"\zs\S\+\ze"\s*$')
            if l:inc ==# a:header_name
                return -1 " 不用添加
            endif
            let l:idx1 = index(s:header_seq,l:inc)

            if l:idx1 == -1 || l:idx1 < l:self_idx " 不在列表中
                let l:ret = i+1 " 下一行
            elseif l:idx1 > l:self_index " 超过
                return l:idx1
            endif
        endif
    endfor
    return l:ret
endfunc

echo MatchHeaderInfo('graph/linkList.hpp')

func! RalgoComlete(findstart,base)
  if a:findstart
      let pos = match(getline('.'), '\(^\|\s\)\zs\S\+\%'.col('.').'c\ze\($\|\s\)')
      "echom pos
      return pos
  else
       echo a:base
       let l:ret_list = []
       for key in keys(g:algo_data)
           "if key =~ a:base
           call add(l:ret_list,{'word': g:algo_data[key].word , 'abbr': g:algo_data[key].abbr})
       endfor
       return l:ret_list
  endif
endfunc

" 执行触发
func! RalgoExpand()
    if has_key(v:completed_item,'user_data') && v:completed_item['user_data'] ==# 'Ralgo_compl'
       call setline(line('.'),v:completed_item['word'] .. 'hello')
    endif
endfunc

func! RalgoSnipComplete()
    let l:line = getline('.')
    let l:start = col('.')-1
    while l:start > 0 && l:line[l:start-1] =~# '\k'
		let l:start -= 1
    endwhile
	let word = l:line[l:start:col('.')]

    let suggestions = []

	for key in keys(g:algo_data)
		if key =~ '^' .. word
			call add(suggestions,{'word': g:algo_data[key].word,'abbr':g:algo_data[key].abbr,'user_data':'Ralgo_compl'})
		endif
	endfor

	if empty(suggestions)
		echohl Error | echon 'no match' | echohl None
	"elseif len(suggestions == 1) "触发
	else
		call complete(l:start+1,suggestions) #? 为什么加1?
	endif
    return ''
endfunc

set completefunc=RalgoComlete
inoremap <c-l> <C-R>=RalgoSnipComplete()<cr>

"i am hello world edge<100> e;

inoremap <expr> <cr> pumvisible() ? "\<c-y>" : "\<c-g>u\<cr>"
inoremap <expr> <tab> pumvisible() ? "\<c-n>" : "\<c-g>u\<tab>"

augroup Ralgo_auto_group
	autocmd!
	autocmd CompleteDone * call RalgoExpand()
augroup END

"edgeArray
