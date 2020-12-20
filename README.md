minesweeper
===========
This program implements a minesweeper board (customizable size) 
and lets you play manually or write strategies that are played by the computer. 

Usage
-----
Compile the program via 
```
make all
```

Launch via 
```
./exec/minesweeper <mode> <height> <width> <mines>
```
where `<height>`, `<width>` give the size of the board, and `<mines>` the number of mines. 
Current modes are: 

| Number | Mode          |
|:------:|---------------|
|0       |Manual play    |
|1       |s_first_click  |
|2       |s_simple_search|

0 is referred for manual play, all other numbers can be used for strategies. 

### Commands
In manual play there are 2 commands, uncover and flagging. The syntax is 
```
(u/f) <y> <x> 
```
Where `u` stands for uncover, and the following 2 numbers are the coordinate of the cell.
Strategies can also give up. 

### Strategies
Currently there are 2 strategies implemented. 
The first one (`s_first_click`) just performs one move: uncovering the cell `0 0` which by default does not have a mine 
on it and then gives up. 

The other strategy (`s_simple_search`) performs a simple search: 
If there is a cell with an equal number of uncovered cells and indicated neighboring mines, these are flagged.
If a cell has all indicated neighboring mines flagged and empty fields nearby, these are uncovered. 
Either this leads to victory or strategy gives up.

Potentially more strategies will be implemented. 

Structure
------------

### Code
Source files in `src`, headers in `include`. 
Object files will be compiled to `obj` and `obj/test`, executables to `exec`. 

### Testing
Some unit tests have been written in `tests`. 
We use the header `minunit.h` taken from https://github.com/siu/minunit.
Unit tests and debugging is not completed. 
We've also used valgrind (https://www.valgrind.org/) for some memory checks/debugging.

TODO
----
- Write more strategies
- Write more unit tests
