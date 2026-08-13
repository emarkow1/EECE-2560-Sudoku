// EECE 2560 Sudoku Project
// 1-satbermacmar-3b
// main.cpp
// authors: Jacob Berman, Ethan Markow, Donald Mackinnon, Emile Sater
// main.cpp reads the sudoku input files, initializes the corresponding boards,
// and solves each sudoku puzzle while displaying results to the user.


#include "board.h"
#include <fstream>
#include <iomanip>
#include <iostream>

using namespace std;

int main()
{
   int numRecursiveCalls = 0;
   int numberOfBoards = 0;

   ifstream fin;
   
   // Read the sample grid from the file.
   string fileName = "sudoku.txt";

   fin.open(fileName.c_str());
   if (!fin)
   {
      throw fileOpenError(fileName);
   }

   try
   {
      board b1(SquareSize);

      while (fin && fin.peek() != 'Z')
      {
      // Read the sample grid from the file.
	   b1.initialize(fin);
      b1.solve();
      cout << "Number of recursive calls: " << b1.getNumRecursiveCalls() << endl;
	   
      numberOfBoards++;
      numRecursiveCalls += b1.getNumRecursiveCalls();
      
      fin >> ws;

      }
   }
   catch  (indexRangeError &ex)
   {
      cout << ex.what() << endl;
      exit(1);
   }
   cout << "The average number of recrusive calls per board is: " << (numRecursiveCalls / numberOfBoards) << endl;
}
