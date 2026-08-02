#include "board.h"

#include <fstream>
#include <iomanip>
#include <iostream>

using namespace std;

int main()
{
    ifstream fin;
    string fileName = "sudoku1.txt";

    fin.open(fileName.c_str());
    if (!fin)
    {
        throw fileOpenError(fileName);
    }

    board b1(SquareSize);
    b1.initialize(fin);
    b1.print();

    return 0;
}