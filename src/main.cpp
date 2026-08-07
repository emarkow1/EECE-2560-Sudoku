// EECE 2560 Sudoku Project
// 1-satbermacmar-3a
// main.cpp
// authors: Jacob Berman, Ethan Markow, Donald Mackinnon, Emile Sater


#include "board.h"
#include <fstream>
#include <iomanip>
#include <iostream>

using namespace std;

int main()
{
   ifstream fin;
   
   // Read the sample grid from the file.
   string fileName = "sudoku1.txt";

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
      // Print the sample grid to the console.
	   b1.print();
      // Test the setCell, resetCell, isSolved, and printConflicts functions
      b1.printConflicts();
      b1.isSolved();
	   
      fin >> ws;

      }
   }
   catch  (indexRangeError &ex)
   {
      cout << ex.what() << endl;
      exit(1);
   }
}
