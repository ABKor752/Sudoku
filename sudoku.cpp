#include "sudoku.h"

Grid::Grid() : grid(vector<vector<char>>(9, vector<char>(9))) {
    int numRows = 0;
    string row = "";
    empty.reserve(81);
    cout << "--- Testing Sudoku grid validity ---\n";
    char starting;
    cin >> starting;
    // Skipping over comments
    while (starting == '/') {
        string junk;
        getline(cin, junk);
        cin >> starting;
    }
    string first = "";
    first += starting;
    while (getline(cin, row)) {
        // Check for more than 9 rows
        if (numRows >= 9) {
            throw InputError("More than 9 rows in input");
        }
        // Account for first character 'starting'
        if (!numRows) row = first + " " + row;

        istringstream iss(row);
        int numCols = 0;
        char space;

        // Read in character by character
        while (iss >> space) {
            // Check for more than 9 columns
            if (numCols >= 9) {
                throw InputError("More than 9 cells in row " + to_string(numRows));
            }
            // Check for unknown characters
            if (!(space >= '1' && space <= '9') && space != '.') {
                string error = "";
                error += space;
                throw InputError("Invalid character \'" + error + 
                    "\' at row " + to_string(numRows) + " column " + to_string(numCols));
            }
            // If cell is empty, insert it into the 'empty' vector
            if (space == '.') empty.push_back({ numRows, numCols });
            // Set the grid cell to the given character
            grid[numRows][numCols++] = space;
        }
        // Check for less than 9 columns
        if (numCols < 9) {
            throw InputError("Less than 9 cells in row " + to_string(numRows));
        }
        ++numRows;
    }
    // Check for less than 9 rows
    if (numRows < 9) {
        throw InputError("Less than 9 rows in input");
    }
    // Check if the initial grid is valid
    if (!validGridFull()) {
        throw InputError("Invalid Sudoku grid");
    }
    cout << "--- Sudoku grid check successful ---\n\n";
    empty.resize(empty.size());
}

bool Grid::validGridFull() const {
    // columns[i] contains all the values seen in the ith column
    vector<unordered_set<char>> columns;
    // blocks[i] contains all the values seen in the ith block
    // A "block" is a 9 x 9 square and is reset every three rows
    vector<unordered_set<char>> blocks;
    columns.resize(9);
    blocks.resize(3);
    for (size_t i = 0; i < grid.size(); ++i) {
        // Reset the blocks if necessary
        if (i % 3 == 0) {
            blocks.clear();
            blocks.resize(3);
        }
        unordered_set<char> row;
        for (size_t j = 0; j < grid[0].size(); ++j) {
            // Check for repeats in row
            if (row.find(grid[i][j]) != row.end()) return false;
            // Check for repeats in column
            if (columns[j].find(grid[i][j]) != columns[j].end()) return false;
            // Check for repeats in block
            if (blocks[j / 3].find(grid[i][j]) != blocks[j / 3].end()) return false;
            // Insert value into the required hash tables
            if (grid[i][j] != '.') {
                row.insert(grid[i][j]);
                columns[j].insert(grid[i][j]);
                blocks[j / 3].insert(grid[i][j]);
            }
        }
    }
    return true;
}

bool Grid::validGridSpace(int index) {
    Cell c = empty[index];
    assert(cellAt(c) != '.');
    // Check row
    for (int i = 0; i < 9; ++i) {
        // Check row
        if (grid[c.row][i] == cellAt(c) && i != c.col) return false;
        // Check col
        if (grid[i][c.col] == cellAt(c) && i != c.row) return false;
    }
    // Determine block bounds
    int left = c.col / 3, bottom = c.row / 3;
    // Check block
    for (int i = 3 * bottom; i < 3 * bottom + 3; ++i) {
        for (int j = 3 * left; j < 3 * left + 3; ++j) {
            if (grid[i][j] == cellAt(c) && i != c.row && j != c.col) return false;
        }
    }
    return true;
}

void Grid::solveSudoku(int numFixed) {
    /* This backtracking method works as follows:
     *      "numFixed" is the number of empty cells which have been filled in
     *      If "numFixed" equals the total number of empty cells, then we have
     *          found a solution
     *      Otherwise, check grid validity when the space is filled in with '1'
     *          through '9'. If the validity check is successful, recurse with
     *          "numFixed" incremented
     */
    if (numFixed == int(empty.size())) {
        found = true;
        return;
    }
    for (char c = '1'; c <= '9'; ++c) {
        cellAt(empty[numFixed]) = c;
        if (validGridSpace(numFixed)) {
            solveSudoku(numFixed + 1);
        }
        // No need to check if we've already found a solution
        if (found) return;
        else cellAt(empty[numFixed]) = '.';
    }
}

void Grid::printGrid(string header) const {
    cout << "------ " << header << " ------\n";
    for (int i = 0; i < int(grid.size()); ++i) {
        for (int j = 0; j < int(grid[i].size()); ++j) {
            cout << grid[i][j] << " ";
            if (j % 3 == 2 && j < int(grid[i].size()) - 1) cout << "| ";
        }
        cout << endl;
        if (i % 3 == 2 && i < int(grid.size()) - 1) {
            for (int j = 0; j < 11; ++j) cout << "- ";
            cout << endl;
        }
    }
    cout << endl;
}