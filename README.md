# TiC89TacToe

An MxN TicTacToe game in C89 that imports a settings file, exports logs and has 3 make conditions.

## Getting Started

Run the make command with any options desired
EDITOR=1 - For editing the settings on the fly, adds menu options.
SECRET=1 - For incognito TicTacToe for all your secretive needs.
NOCLEAR=1 - For single output (no linux "clear" command) useful for debugging.

# Files
## 11 Files
settings.txt - sample settings

### Headers
UserInterface.h
FileIO.h
gameEngine.h
logs.h
linked_list.h

### C Files
FileIO.c
gameEngine.c
UserInterface.c
logs.c
linked_list.c

### Prerequisites

A competitive spirit, a linux OS, a keyboard and a friend or multiple personalities.

make ./TiC89TacToe settings.txt

### Installing

1. make using arguments desired
2. ensure valid settings file

and play to your heart's content.

If you want to save the game logs, from the menu select option 5 (not available in secret mode).

## Debugging / testing

Make with noclear so the output remains intact and analyse with a debugger of your choice.

## Deployment

Run using ./TiC89TacToe <settings_file>

## Built With

* [vim](https://www.vim.org) - The editor used
* [valgrind](http://valgrind.org) - Memory checks
* [gdb](https://www.gnu.org/software/gdb/) - Debugger tool


## Authors

* [retro-node](https://github.com/retro-node)

## Acknowledgments

* Adam Rosenfield - whos Stack Overflow post helped me fix file time by initialising with NULL
* geeksforgeeks.org - for inspiring my Press enter to continue that saved a lot of input buffer issues
