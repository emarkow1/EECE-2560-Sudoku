# EECE-2560-Sudoku

## Sudoku Grid

Sudoku is a game in which a 9x9 grid made up of 3x3 blocks. Each row, column, and block must contain each digit 1-9 exactly once.

## Part A:

Implements the framework for a sudoku solver based on a backtracking algorithm. The program creates a blank sudoku grid, then fills it with the values taken from a filename specified in [main.cpp](main.cpp) (e.g. [sudoku1.txt](sudoku1.txt), [sudoku2.txt](sudoku2.txt), etc.). The program prints out the board, then tests setting a cell to a value and resetting the cell to a value, printing out the resulting board. The program finishes by checking if the board is solved and printing out the conflicts matrix, which implements the conflict counts approach.

### Function Implementations

`initialize`: Reads a sudoku board from the specifiec input file

`updateConflicts`: Updates the conflicts matrix using the improved confict counts approach. Called whenever a change is made to the board.

`print`: prints the current sudoku board to the terminal.

`printConflicts`: prints the conflicts matrix to the terminal.

`setCell`: Updates the value of a cell and calls `updateConflicts` if the intended value is valid. Otherwise throws an error.

`resetCell`: Resets a cell to blank and calls `updateConflicts`.

`isSolved`: Checks if the board is full and all cells have valid entries and prints the result to the terminal.

## Building and Running the Program

[CMakeLists.txt](CMakeLists.txt) will build the program.

Configure CMake with:
```
cmake -S . -B build
```

Then build the program with:
```
cmake --build build
```

Then the program can be run with:
```
./build/sudoku
```