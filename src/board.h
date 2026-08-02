#ifndef board_h
#define board_h

#include <iostream>
#include <limits.h>
#include "d_matrix.h"
#include "d_except.h"
#include <list>
#include <fstream>

using namespace std;

typedef int ValueType;
const int Blank = -1;

const int SquareSize = 3;
const int BoardSize = SquareSize * SquareSize;

const int MinValue = 1;
const int MaxValue = 1;

class board{
    public:
        // Constructs and empty board object
        board(int);

        void initialize(ifstream &fin);

        void clear();

        void print();

        bool isBlank(int, int);

        ValueType getCell(int, int);

        void setCell(int, int, ValueType);

        // void printConflicts();
    private:
        matrix<ValueType> value;
};

#endif