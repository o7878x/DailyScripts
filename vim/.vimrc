" All system-wide defaults are set in $VIMRUNTIME/debian.vim and sourced by
" the call to :runtime you can find below.  If you wish to change any of those
" settings, you should do it in this file (/etc/vim/vimrc), since debian.vim
" will be overwritten everytime an upgrade of the vim packages is performed.
" It is recommended to make changes after sourcing debian.vim since it alters
" the value of the 'compatible' option.

" This line should not be removed as it ensures that various options are
" properly set to work with the Vim-related packages available in Debian.
runtime! debian.vim

" Vim will load $VIMRUNTIME/defaults.vim if the user does not have a vimrc.
" This happens after /etc/vim/vimrc(.local) are loaded, so it will override
" any settings in these files.
" If you don't want that to happen, uncomment the below line to prevent
" defaults.vim from being loaded.
" let g:skip_defaults_vim = 1

" Uncomment the next line to make Vim more Vi-compatible
" NOTE: debian.vim sets 'nocompatible'.  Setting 'compatible' changes numerous
" options, so any other options should be set AFTER setting 'compatible'.
"set compatible

" Vim5 and later versions support syntax highlighting. Uncommenting the next
" line enables syntax highlighting by default.
syntax on

" If using a dark background within the editing area and syntax highlighting
" turn on this option as well
"set background=dark

" Uncomment the following to have Vim jump to the last position when
" reopening a file
"if has("autocmd")
"  au BufReadPost * if line("'\"") > 1 && line("'\"") <= line("$") | exe "normal! g'\"" | endif
"endif

" Uncomment the following to have Vim load indentation rules and plugins
" according to the detected filetype.
"if has("autocmd")
"  filetype plugin indent on
"endif

" The following are commented out as they cause vim to behave a lot
" differently from regular Vi. They are highly recommended though.
"set showcmd		" Show (partial) command in status line.
"set showmatch		" Show matching brackets.
"set ignorecase		" Do case insensitive matching
"set smartcase		" Do smart case matching
"set incsearch		" Incremental search
"set autowrite		" Automatically save before commands like :next and :make
"set hidden		" Hide buffers when they are abandoned
"set mouse=a		" Enable mouse usage (all modes)

" Source a global configuration file if available
if filereadable("/etc/vim/vimrc.local")
  source /etc/vim/vimrc.local
endif

" Molokai colorscheme comment
"set t_co=256
"colorscheme molokai
"let g:molokai_original = 1
"let g:reshash256 = 1

set t_co=256
colorscheme slate

set number              " Display row number
set ignorecase          " Do case unsensitive matching

set ruler               " Display ruler

set noeb                " Hide error sound
set vb t_vb=

set autoindent          " Set auto indent
set cindent             " Set C language type indent

set tabstop=4           " Set `tab` key width
set shiftwidth=4        " Liked above
set softtabstop=4       " Liked above

set expandtab           " Replace `tab` with `space`

set history=100         " Limit max command history

set nobackup            " Set no backup file
set noswapfile          " Set no swap file

"set confirm             " Ask for confimo

set nohlsearch            " Set highlight search
set showmatch           " Set highlight match

set autoread            " Auto update file when changed

filetype plugin indent on " Auto detect file type

autocmd FileType * setlocal formatoptions-=c formatoptions-=r formatoptions-=o      " Disable auto comment (details see http://vim.wikia.com/wiki/Disable_automatic_comment_insertion )

" Compile c source code
func! CompileC()
    exec "w"
    let compilecmd="!gcc "
    let compileflag="-o %< "
    if search("mpi\.h") != 0
        let compilecmd = "!mpicc "
    endif
    if search("glut\.h") != 0
        let compilecmd .= " -lglut -lGLU -lGL "
    endif
    if search("cv\.h") != 0
        let compilecmd .= " -lcv -lhighgui -lcvaux "
    endif
    if search("omp\.h") != 0
        let compilecmd .= " -fopenmp "
    endif
    if search("math\.h") != 0
        let compilecmd .= " -lm "
    endif
    exec  compilecmd." % ".compileflag
endfunc

" Compile cpp source code
func! CompileCpp()
    exec "w”
    let compilecmd="!g++ "
    let compileflag="-o %< "
    if search("mpi\.h") != 0
        let compilecmd = "!mpic++ "
    endif
    if search("glut\.h") != 0
        let compilecmd .= " -lglut -lGLU -lGL "
    endif
    if search("cv\.h") != 0
        let compilecmd .= "-lcv -lhighgui -lcvaux "
    endif
    if search("omp\.h") != 0
        let compilecmd .= " -fopenmp "
    endif
    if search("math\.h") != 0
        let compilecmd .= " -lm "
    endif
    exec compilecmd." % ".compileflag
endfunc

" Compile java source dode
func! CompileJava()
    exec "w"
    exec "!javac %"
endfunc

" Compile common source code
func! CompileCode()
    exec "w"
    if &filetype == "cpp"
        exec "call CompileCpp()"
    elseif &filetype == "c"
        exec "call CompileC()"
    elseif &filetype == "java"
        exec "call CompileJava()"
    endif
endfunc

" Run c language executable
func! RunC()
    exec "! ./%<"
endfunc

" Run cpp lanuage executable
func! RunCpp()
    exec "! ./%<"
endfunc

" Run Java byte code
func! RunJava()
    exec "! java %<"
endfunc

" Run python code
func! RunPython()
    exec "!python %"
endfunc

" Run source code common interface
func! RunCode()
    exec "w"
    if &filetype == "cpp"
        exec "call Runc()"
    elseif &filetype == "c"
        exec "call RunCpp()"
    elseif &filetype == "py"
        exec "call RunPython()"
    elseif &filetype == "java"
        exec "call RunJava()"
    endif
endfunc

"Fast run source code
func! TestCode()
    exec "w"
    if &filetype == "c"
        exec "!gcc -Wall % -o %< && ./%<"
    elseif &filetype == "cpp"
        exec "!g++ -Wall -std=c++11 -lpthread % -o %< && ./%<"
    elseif &filetype == "python"
        exec "!python %"
    elseif &filetype == "java"
        exec "!javac % && java %<"
    elseif &filetype == "javascript"
        exec "!node %"
    endif
endfunc

" Measure the running time of source code
func! MeasureCode()
    exec "w"
    if &filetype == "c"
        exec "!gcc -Wall % -o %< && time ./%<"
    elseif &filetype == "cpp"
        exec "!g++ -Wall % -o %< && time ./%<"
    elseif &filetype == "python"
        exec "!time python %"
    elseif &filetpye == "java"
        exec "!javac % && time java %<"
    endif
endfunc

map <F5> : call TestCode()<CR>
map <F6> : call MeasureCode()<CR>
map <F7> : call CompileCode()<CR>
map <F8> : call RunCode()<CR>
