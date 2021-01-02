#ifndef SUDOKU_H_
#define SUDOKU_H_

#include <iostream>
#include <sstream>
#include <unordered_set>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
#include <cassert>
using namespace std;

// Custom exception for input errors
class InputError : public exception {
private:
    string msg;
public:
    InputError(string msg) : msg(msg) {};

    const char * what() const noexcept override {
        return msg.c_str();
    }
};

class Grid {
private:
    struct Cell {
        int row;
        int col;
    };

    // 9 x 9 sudoku board, where '.' represents an empty cell
    vector<vector<char>> grid;

    // vector of the empty cells in the grid
    vector<Cell> empty;

    // set to true if a solution was found
    bool found = false;

    // Checks if the entire grid has any inconsistencies
    bool validGridFull() const;


    // Checks if the grid has inconsistencies after adding a single cell
    bool validGridSpace(int index);

    // Returns the character at the specified cell
    char& cellAt(const Cell& c) {
        return grid[c.row][c.col];
    }
public:
    // Default constructor, reads in entire input and throws an InputError
    // if necessary
    Grid();

    // Solves the Sudoku puzzle using backtracking
    void solveSudoku(int numFixed);

    // Prints "--- [header] ---", followed by the current Sudoku puzzle
    void printGrid(string header) const;
};

#endif