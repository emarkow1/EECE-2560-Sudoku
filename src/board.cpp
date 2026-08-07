// EECE 2560 Sudoku Project
// 1-satbermacmar-3a
// board.cpp
// authors: Jacob Berman, Ethan Markow, Donald Mackinnon, Emile Sater
// This file contains the implementation of the board class, which represents a
// Sudoku board.

// Declarations and functions for project #3
#include "board.h"
using namespace std;

// Global variable for tracking the number of solutions 
// and recursive calls. Included from teacher provided code 
// for part b
//int numSolutions = 0; 


board::board(int sqSize)
   : value(BoardSize+1,BoardSize+1), conflicts(BoardSize+1, BoardSize+1)
// Board constructor
{
   clear();
}

void board::clear()
// Mark all possible values as legal for each board entry
{
    for (int i = 1; i <= BoardSize; i++)
    {
        for (int j = 1; j <= BoardSize; j++)
        {
            value[i][j] = Blank;
            conflicts[i][j].assign(BoardSize, 0);
        }
    }
}

void board::initialize(ifstream &fin)
// Read a Sudoku board from the input file.
{
   char ch;

   clear();
   
   for (int i = 1; i <= BoardSize; i++){
      for (int j = 1; j <= BoardSize; j++)
	   {
	       fin >> ch;
         if (ch == '.')
         {
            continue;
         }
          // If the read char is not Blank
	      if (ch >= '1' && ch <= '9')
         {
             setCell(i,j,ch-'0');   // Convert char to int
         }
         else
         {
            throw fileError("Invalid number/character in sudoku board");
         }
      }
   }
}

int squareNumber(int i, int j)
// Return the square number of cell i,j (counting from left to right,
// top to bottom.  Note that i and j each go from 1 to BoardSize
{
   // Note that (int) i/SquareSize and (int) j/SquareSize are the x-y
   // coordinates of the square that i,j is in.  

   return SquareSize * ((i-1)/SquareSize) + (j-1)/SquareSize + 1;
}

ostream &operator<<(ostream &ostr, vector<int> &v)
// Overloaded output operator for vector class.
{
   for (int i = 0; i < v.size(); i++)
   {
      ostr << v[i] << " ";
   }

   ostr << endl;
   return ostr; 
}

ValueType board::getCell(int i, int j)
// Returns the value stored in a cell.  Throws an exception
// if bad values are passed.
{
   if (i >= 1 && i <= BoardSize && j >= 1 && j <= BoardSize)
   {
      return value[i][j];
   }
   else
   {
      throw rangeError("bad value in getCell");
   }
}

bool board::isBlank(int i, int j)
// Returns true if cell i,j is blank, and false otherwise.
{
   if (i < 1 || i > BoardSize || j < 1 || j > BoardSize)
   {
      throw rangeError("bad value in setCell");
   }

   return (getCell(i,j) == Blank);
}

void board::print()
// Prints the current board.
{
   for (int i = 1; i <= BoardSize; i++)
   {
      if ((i-1) % SquareSize == 0)
      {
         cout << " -";
	 for (int j = 1; j <= BoardSize; j++)
	    cout << "---";
         cout << "-";
	 cout << endl;
      }
      for (int j = 1; j <= BoardSize; j++)
      {
	 if ((j-1) % SquareSize == 0)
	    cout << "|";
	 if (!isBlank(i,j))
	    cout << " " << getCell(i,j) << " ";
	 else
	    cout << "   ";
      }
      cout << "|";
      cout << endl;
   }

   cout << " -";
   for (int j = 1; j <= BoardSize; j++)
      cout << "---";
   cout << "-";
   cout << endl;
}

//This sets the cell to a value and updates the conflicts
// of the cells that are effected. There is error checking
// to make sure the value and position are valid. 
void board::setCell(int row, int col, ValueType val)
{
   if (row < 1 || row > BoardSize || col < 1 || col > BoardSize)
   {
      throw rangeError("bad position in setCell");
   }
   
   if (val < MinValue || val > MaxValue)
   {
      throw rangeError("bad value in setCell");
   }

  if (!isBlank(row, col))
  {
      throw rangeError("cell is not blank in setCell");
  }
   value[row][col] = val;
   updateConflicts(row, col, 1);
   }

//prints all the conflicts with a for loop.
void board::printConflicts()
{
   for (int i = 1; i <= BoardSize; i++)
   {
      for (int j = 1; j <= BoardSize; j++)
      {
         cout << "Cell (" << i << "," << j << "): ";
         cout << conflicts[i][j];
      }
      cout << endl;
   }
}

//This function updates the conflicts the cells effected when a certain 
// cell is changed
void board::updateConflicts(int row, int col, int change)
{

   // stores the value of the cell being added or removed.
   ValueType val = value[row][col];
   
   if (val == Blank)
   {
      return;
   }

   // adjusts sudoku index (1 to 9) to proper vector index (0 to 8)
   int vecIndex = val - 1;

   // adjusts conflict count for specific 'vecIndex' digit in every other cell
   // within same row
   for (int j = 1; j <= BoardSize; j++)
   {
      
      if (j != col)
      {
         conflicts[row][j][vecIndex] += change;
      }
   }

   // adjusts conflict count for specific 'vecIndex' digit in every other cell
   // within same column
   for (int i = 1; i <= BoardSize; i++)
   {
      if (i != row)
      {
         conflicts[i][col][vecIndex] += change;
      }
   }

   // To understand what digits belong to each square, the upper left row and
   // upper left column of EACH square (firstRow and firstCol) are found.
   int firstRow = ((row-1) / SquareSize) * SquareSize + 1;

   int firstCol = ((col - 1) / SquareSize) * SquareSize + 1;

   // now understanding firstRow location and firstCol location of the sudoku
   // squares, conflicts can be adjusted for each of the squares on the sudoku
   // board.
   for (int i = firstRow; i < firstRow + SquareSize; i++)
   {
      for (int j = firstCol; j < firstCol + SquareSize; j++)
      {
         if (i != row || j != col)
         {
            conflicts[i][j][vecIndex] += change;
         }
      }
   }
}

//Determines if the board is solved by checking if any cell is blank
// or if any cell has a conflict. If either condition is true, the board
// is not solved. Otherwise, the board is solved.
bool board::isSolved()
{
   
   for (int i = 1; i <= BoardSize; i++)
   {
      for (int j = 1; j <= BoardSize; j++)
      {
         int cellValue = getCell(i,j);
         if (isBlank(i,j) || conflicts[i][j][cellValue-1] > 0)
         {
            cout << "The board is not solved." << endl;
            return false;
         }
      }
   }
   cout << "The board is solved" << endl;
   return true;
}

//This is used to reset a cell back to blank and update all the
//conflicts to the change.
void board::resetCell(int row, int col)
{
   if (row < 1 || row > BoardSize || col < 1 || col > BoardSize)
   {
      throw rangeError("bad position in resetCell");
   }

   if (isBlank(row, col))
   {
      return;
   }

   updateConflicts(row, col, -1);

   value[row][col] = Blank;
}

