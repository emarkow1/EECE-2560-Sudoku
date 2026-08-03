// Declarations and functions for project #4
#include "board.h"


using namespace std;

int numSolutions = 0; // int numRecursiveCall = 0 for part b


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
      for (int j = 1; j <= BoardSize; j++)
      {
         value[i][j] = Blank;
      }
   updateConflicts();
}

void board::initialize(ifstream &fin)
// Read a Sudoku board from the input file.
{
   char ch;

   clear();
   
   for (int i = 1; i <= BoardSize; i++)
      for (int j = 1; j <= BoardSize; j++)
	    {
	       fin >> ch;

          // If the read char is not Blank
	      if (ch != '.')
             setCell(i,j,ch-'0');   // Convert char to int
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
      ostr << v[i] << " ";   
   cout << endl;
   
   // I added this to prevent a warning about no return value. It was not in the original code
   return ostr; 
}

ValueType board::getCell(int i, int j)
// Returns the value stored in a cell.  Throws an exception
// if bad values are passed.
{
   if (i >= 1 && i <= BoardSize && j >= 1 && j <= BoardSize)
      return value[i][j];
   else
      throw rangeError("bad value in getCell");
}

bool board::isBlank(int i, int j)
// Returns true if cell i,j is blank, and false otherwise.
{
   if (i < 1 || i > BoardSize || j < 1 || j > BoardSize)
      throw rangeError("bad value in setCell");

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

void board::setCell(int i, int j, ValueType val)
{
   if (i < 1 || i > BoardSize || j < 1 || j > BoardSize)
      throw rangeError("bad value in setCell");

   value[i][j] = val;
   updateConflicts();
}

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

//need to change slightly right now it goes through entire matrix isntead of only effected cells
void board::updateConflicts()
{
   for (int i = 1; i <= BoardSize; i++)
   {
      for (int j = 1; j <= BoardSize; j++){
         conflicts[i][j].resize(9);
         for (int k = 0; k < 9; k++) {
            conflicts[i][j][k] = 0;

            for (int m = 1; m <= BoardSize; m++) {
               if (j != m && value[i][m] == k + 1) {
                  conflicts[i][j][k]++;
               }
            }
            for (int m = 1; m <= BoardSize; m++) {
               if (i != m && value[m][j] == k + 1) {
                  conflicts[i][j][k]++;
               }
            }

            int rowCorner = ((i - 1) / SquareSize) * SquareSize + 1;
            int colCorner = ((j - 1) / SquareSize) * SquareSize + 1;
            for (int m = rowCorner; m < rowCorner + SquareSize; m++) {
               for (int n = colCorner; n < colCorner + SquareSize; n++) {
                  if (!(i == m && j == n) && value[m][n] == k + 1) {
                     conflicts[i][j][k]++;
                  }
               }
            }
         }
      }
   }
}

bool board::isSolved()
{
   for (int i = 1; i <= BoardSize; i++) {
      for (int j = 1; j <= BoardSize; j++) {
         int cellValue = getCell(i,j);
         if (isBlank(i,j) || conflicts[i][j][cellValue-1] > 0) {
            cout << "The board is not solved.";
            return false;
         }
      }
   }
   cout << "The board is solved";
   return true;
}

void board::resetCell(int i, int j) {
   
}