// EECE 2560 Sudoku Project
// 1-satbermacmar-3a
// board.h
// authors: Jacob Berman, Ethan Markow, Donald Mackinnon, Emile Sater
// This is the board header file to declare the class board
// Declarations and functions for project #3


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

        // Intializes the board object with values from the input file
        void initialize(ifstream &fin);

        // clear the board object to be blank
        void clear();

        // prints the board object to the console
        void print();

        // returns if a cell is blank or not with true or false
        bool isBlank(int, int);

        // returns the value of a cell
        ValueType getCell(int, int);

        /// sets a cell to a value and updates conflicts
        void setCell(int, int, ValueType); 

        //prints the conflicts
        void printConflicts(); 

        //Checks if the board is solved
        bool isSolved(); 

        // reset cell back to -1 and update the conflicts.
        void resetCell(int, int); 

    private:
        // updates the conflicts of the cells that are effected 
        // by a change
        void updateConflicts(int row, int col, int change);

        // data members for the board class
        matrix<ValueType> value;
        matrix<vector<int> > conflicts;

};

#endif