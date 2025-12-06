//boilerplate c++
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

//function to count number of @'s in a 3x3 matrix
int countNeighbors(const vector<string>& grid, int row, int col) {
    int count = 0;
    int numRows = grid.size();
    int numCols = grid[0].size();

    // check 3x3 neighborhood
    for (int dr = -1; dr <= 1; dr++) {
        for (int dc = -1; dc <= 1; dc++) {
            if (dr == 0 && dc == 0) continue; // skip the center cell

            int newRow = row + dr;
            int newCol = col + dc;

            // check bounds
            if (newRow >= 0 && newRow < numRows &&
                newCol >= 0 && newCol < numCols) {
                if (grid[newRow][newCol] == '@') {
                    count++;
                }
            }
        }
    }
    return count;
}

int main() {
    //example input grid:
    vector<string> grid;
    string line;

    ifstream infile("input.txt");
    while (getline(infile, line)) {
        if(!line.empty()) {
        grid.push_back(line);
        }
    }
    int counter = 0;

    //traverse the grid
    for (int r = 0; r < grid.size(); r++) {
        for (int c = 0; c < grid[r].size(); c++) {
            //if current cell is '@', count its neighbors
            if (grid[r][c] == '@') {
                int neighbors = countNeighbors(grid, r, c);
                if (neighbors < 4) {
                    counter++;
                }
            }
        }
    }
    cout << "Total '@' cells with fewer than 4 '@' neighbors: " << counter << endl;
    return 0;
}