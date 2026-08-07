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
	   b1.initialize(fin);
	   b1.print();
      b1.setCell(1, 2, 5);
      b1.print();
      b1.resetCell(1, 2);
      b1.print();
      b1.isSolved();
      b1.printConflicts();
	   
      }
   }
   catch  (indexRangeError &ex)
   {
      cout << ex.what() << endl;
      exit(1);
   }
}
