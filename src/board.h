// EECE 2560 Sudoku Project
// 1-satbermacmar-3a
// board.cpp
// authors: Jacob Berman, Ethan Markow, Donald Mackinnon, Emile Sater

#ifndef board_h
#define board_h

#include <iostream>
#include <limits.h>
#include <list>
#include <fstream>
#include <vector>

#include "d_matrix.h"
#include "d_except.h"

using namespace std;

typedef int ValueType; // The type of the value in a cell
const int Blank = -1;  // Indicates that a cell is blank
 
const int SquareSize = 3;  //  The number of cells in a small square
                           //  (usually 3).  The board has
                           //  SquareSize^2 rows and SquareSize^2
                           //  columns.

const int BoardSize = SquareSize * SquareSize;

const int MinValue = 1;
const int MaxValue = 9;


class board{
    public:
        // Constructs and empty board object
        board(int);

        void initialize(ifstream &fin);

        void clear();

        void print();

        bool isBlank(int, int);

        ValueType getCell(int, int);

        /// sets a cell to a value and updates conflicts
        void setCell(int, int, ValueType); 

        void printConflicts(); //prints the conflicts

        bool isSolved(); //Checks if the board is solved

        void resetCell(int, int); // reset cell back to -1 and update the conflicts.

    private:
        void updateConflicts(int row, int col, int change);

        matrix<ValueType> value;
        matrix<vector<int> > conflicts;

};

#endif