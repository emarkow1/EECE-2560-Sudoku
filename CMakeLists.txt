cmake_minimum_required(VERSION 3.10.0)
project(sudoku VERSION 0.1.0 LANGUAGES C CXX)

add_executable(sudoku
    src/main.cpp
    src/board.cpp
    )

target_include_directories(sudoku PRIVATE src)

