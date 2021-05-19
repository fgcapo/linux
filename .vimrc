set path=~/cruise/ros/src/**

":set background=dark
"
"if has('syntax')
"    syntax enable             " Turn on syntax highlighting
"    silent! colorscheme eldar " Custom color scheme
"endif

:set nu
:set mouse=a
:set smartindent autoindent expandtab shiftwidth=4 tabstop=4

" to disable search highlighting temporarily, use :noh
:set hlsearch

let g:clang_format_path = '/usr/local/bin/clang-format'
"let g:formatterpath = ['/usr/local/bin/clang-format']
"map <C-K> :pyf /usr/share/vim/addons/syntax/clang-format-3.8.py<cr>
"imap <C-K> <c-o>:pyf /usr/share/vim/addons/syntax/clang-format-3.8.py<cr>
map <C-K> :w<cr>:!clang-format -i %<cr>:e<cr>
"imap <F5> <Esc>:wa<cr>:Bazel build //...<cr>
nnoremap <Leader>o o<Esc>
nnoremap <Leader>O O<Esc>

" \q close file without closing window
map <leader>q :bp<bar>sp<bar>bn<bar>bd<CR>
map <leader>l :diffget LOCAL<CR>

" Use YAPF for Python
let g:formatters_python = ['yapf']
" Use ctrl+k to invoke the auto-formatter
"map <C-K> :Autoformat<cr>
"imap <C-K> <c-o>:Autoformat<CR>

function! BuildYCM(info)
  " info is a dictionary with 3 fields
  " - name:   name of the plugin
  " - status: 'installed', 'updated', or 'unchanged'
  " - force:  set on PlugInstall! or PlugUpdate!
  if a:info.status == 'installed' || a:info.force
    !./install.py --clang-completer
  endif
endfunction

" Plugin manager: https://github.com/junegunn/vim-plug
" To begin, download plug.vim from the above repo to the autoload folder
" ~/.vim/autoload
"
" Automatically install Plug plugin installer
" if empty(glob('~/.vim/autoload/plug.vim'))
"   silent !curl -fLo ~/.vim/autoload/plug.vim --create-dirs
"     \ https://raw.githubusercontent.com/junegunn/vim-plug/master/plug.vim
"   autocmd VimEnter * PlugInstall --sync | source $MYVIMRC
" endif

" Specify a directory for plugins (:PlugInstall to update plugins)
" - For Neovim: ~/.local/share/nvim/plugged
" - Avoid using standard Vim directory names like 'plugin'
call plug#begin('~/.vim/plugged')

" Make sure you use single quotes

"Plug 'editorconfig/editorconfig-vim'

"Plug 'agude/vim-eldar'

" Plug 'tpope/vim-dispatch'
" Plug 'vim-scripts/a.vim'
Plug 'derekwyatt/vim-fswitch'

" Sensible vim defaults, little better than just nocompatible
" Plug 'tpope/vim-sensible'

" Shorthand notation; fetches https://github.com/junegunn/vim-easy-align
Plug 'junegunn/vim-easy-align'

" Any valid git URL is allowed
Plug 'https://github.com/junegunn/vim-github-dashboard.git'

" Multiple Plug commands can be written in a single line using | separators
"Plug 'SirVer/ultisnips' | Plug 'honza/vim-snippets'

" On-demand loading
Plug 'scrooloose/nerdtree', { 'on':  'NERDTreeToggle' }
Plug 'tpope/vim-fireplace', { 'for': 'clojure' }

" Using a tagged release; wildcard allowed (requires git 1.9.2 or above)
Plug 'fatih/vim-go', { 'tag': '*' }

" Plugin options
Plug 'nsf/gocode', { 'tag': 'v.20150303', 'rtp': 'vim' }

" Plugin outside ~/.vim/plugged with post-update hook
Plug 'junegunn/fzf', { 'dir': '~/.fzf', 'do': './install --all' }

" Unmanaged plugin (manually installed and updated)
Plug '~/my-prototype-plugin'

" Vim plugin for ROS dev
" Plug 'taketwo/vim-ros'
"
" Add maktaba and bazel to the runtimepath.
" (The latter must be installed before it can be used.)
Plug 'google/vim-maktaba'
Plug 'bazelbuild/vim-bazel'

"Plug 'Valloric/YouCompleteMe'

" Using a non-master branch
"Plug 'rdnetto/YCM-Generator', { 'branch': 'stable' }


" To handle automatic ctag genration
" Plug 'xolox/vim-easytags'

" Needed by vim-easytags
" Plug 'xolox/vim-misc'


" Initialize plugin system
call plug#end()


" derekwyatt/vim-fswitch
nmap <silent> <Leader>a :FSHere<CR>
nmap <silent> <Leader>sh :FSSplitLeft<CR>
nmap <silent> <Leader>sl :FSSplitRight<CR>
nmap <silent> <Leader>sj :FSSplitBelow<CR>
nmap <silent> <Leader>sk :FSSplitAbove<CR>
let g:fsnonewfiles=1
autocmd! BufEnter *.cpp let b:fswitchdst = 'h,hpp'
            \ | let b:fswitchlocs = 'reg:|\(.*\)src|\1include/**/|,
            \                        reg:/src/include/,
            \                        reg:|src|include/**|,
            \                        ../include'
autocmd! BufEnter *.h let b:fswitchdst  = 'cpp,c'
            \ | let b:fswitchlocs =  'reg:|\(.*\)include\(.*\)|\1src/**|,
            \                         reg:/include/src/,
            \                         reg:/include.*/src/,
            \                         ../src'

":set tags=~/cruise/ros/src/tags
let g:ycm_global_ycm_extra_conf = '$HOME/cruise/.ycm_extra_conf.py'

