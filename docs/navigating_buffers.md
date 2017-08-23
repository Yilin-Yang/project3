# Navigating Buffers in Vim

## What's a buffer (in the context of vim)?
A **buffer** is a location in memory containing a "working copy" of a file
that you're editing in vim.

## Why buffers?
Vim does not edit text files directly. If you open a file in vim, delete a
few words, and then open that same text file from another text editor--gedit,
let's say--then gedit will not show those words missing.

However, if you delete those words and then _write_ the text file using
`:w<cr>` (literally the key sequence "shift-semicolon, lowercase-w,
enter/(carriage) return" while in normal mode), _then_ open the file in
gedit, then gedit _will_ show the changes.

When you're editing a file in vim, you're editing a "working copy" of that
file in a **buffer**, not the original file itself. There are a few reasons
why vim does this:
* Something can go wrong that breaks vim. (Vim could crash, or your
  computer could lose power, and so on.) If vim were editing your text
  file _directly,_ then that could corrupt your text file.
* Reading and writing to hard disks is slow. On the other hand, reading and
  writing to memory (RAM) is extremely fast.
  	* You probably wouldn't notice a speed difference if you're editing
	  small files, but when you're using vim to edit gargantuan text files
	  (e.g. multi-megabyte log files), the slowdown would be more noticeable.
  	* Editing files in a buffer means that you're writing to memory _until_
	  you're ready to write to a file. Vim can respond immediately when you
	  type or delete characters or words and only write to the file when
	  you want it to.

## What does this have to do with file navigation?
If you open a file in vim, and then open another file in that same vim
window (`:e another_file.txt<cr>`), vim stores buffers for both of those
files.

You can list these buffers with `:buffers<cr>`.

When you "goto file" (highlight a filename with your terminal's cursor and
type `gf` in normal mode), this opens the file in a new buffer ("buffer 2").

If you "goto" another file within "buffer 2", you'll be plopped into a new
buffer ("buffer 3") containing the text of that third file.

## How do you switch between these buffers?

**If you only went "one level deep"** (i.e. you have a "buffer 1" and a
"buffer 2"), use `CTRL-^` (hold control, shift-number-row-6, release
control) to _toggle between them._

This lets you jump to a file with `gf`, then return to the previous file
when you're done looking. You can also reopen that file by hitting `CTRL-^`
again.

**If you went "multiple levels deep"** (i.e. `num_buffers > 2`), use
`:buffers<cr>` to list the buffers, and use `:e #{NO_OF_BUFFER_TO_JUMP_TO}<cr>`.

This is a more "purposeful" method of navigation.

## Hidden Buffers
Ordinarily, you're not allowed to go to another buffer if you haven't saved
the current one. In other words, if there's a `[+]` in your statusline next
to the name of the current file, then you aren't allowed to leave that
buffer without `:w<cr>`ing first.

If you don't like that, you can `:set hidden<cr>` to turn that
behavior off. You'll be able to go to new buffers without saving the old
one, although vim will still yell at you if you try exiting (`:q<cr>`)
without writing those older buffers.

If you want to make that behavior persistent, edit your `~/.vimrc` and add
the line `set hidden`, without the colon.


Also, consider using:
* [Tabs](http://vim.wikia.com/wiki/Using_tab_pages)
	* These are functionally similar to tabs in a web browser.
* The [NerdTree plugin](https://github.com/scrooloose/nerdtree)
	* Opens a list of files in the current directory that you can use to
	  more easily hop between files.
* [ctags](https://en.wikipedia.org/wiki/Ctags) and
  [vim-easytags](https://github.com/xolox/vim-easytags)
  	* Lets you cursor-select function prototypes, variables, class types,
	  etc. and jump directly to their definitions. Useful for figuring out
	  how large codebases work.
	* If you're using `vim-easytags`, make sure that you turn on
	  asynchronous (i.e. multithreaded) tag generation!
