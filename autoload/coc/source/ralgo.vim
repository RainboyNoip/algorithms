" vim source for algorithms : github.com/RainboyNoip/algorithms 
"
function! coc#source#ralgo#init() abort
  return {
        \ 'priority': 99,
        \ 'shortcut': '🌂',
        \ 'filetypes': ['cpp'],
        \ 'triggerCharacters': ['@']
        \}
endfunction

function! coc#source#ralgo#complete(opt, cb) abort
    call a:cb(ralgo#data#GetComplete())
endfunction
