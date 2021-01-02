#include <iostream>
#include <chrono>
#include "sudoku.h"
using namespace std;
using namespace chrono;

/**
 * This program assumes that the input Sudoku puzzle has a UNIQUE SOLUTION.
 * If there are multiple solutions, it will print the first one it finds.
 * 
 * To run, do the following:
 *      make solver
 *      ./solver < [input file]
 *
 * The input file should be formatted as follows:
 *      // Any comments should be at the top of the file
 *      /  And start with one or two slashes
 *      [9 x 9 puzzle, each row on a new line, using the characters
 *       '1' through '9' to represent given numbers and '.' to 
 *       represent empty cells]
 */
int main() {
    auto start = high_resolution_clock::now();
    try {
        Grid g;
        g.printGrid("Initial");
        // Solve sudoku and print
        g.solveSudoku(0);
        g.printGrid("Solution");
        // Calculate runtime and print
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<milliseconds>(stop - start);
        cout << "--- Runtime ---\n";
        cout << duration.count() << " milliseconds\n";
    }
    catch (const InputError& e) {
        cout << "InputError: " << e.what() << endl;
        return 1;
    }
    return 0;
}