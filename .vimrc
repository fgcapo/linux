filetype plugin indent on
set nu
" show existing tab with spaces width
set tabstop=2
" when indenting with '>', use spaces width
set shiftwidth=2
" On pressing tab, insert spaces
set expandtab
" execute current file
"map <F9> :w<CR> :! rm %<<CR> :!clear; make<CR> :!./%<<CR> :copen<CR>
"map <F5> :w<CR> :! rm %<<CR> :!clear<CR> :make<CR>
map <F5> :w<CR> :! rm %<<CR> :!clear<CR> :make<CR> :!./%<<CR>
"nnoremap <F9> :!%:p
