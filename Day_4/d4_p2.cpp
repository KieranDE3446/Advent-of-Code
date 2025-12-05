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
    infile.close();
    bool changed = true;
    int pass = 0;
    int totalRemoved = 0;
    while (changed) {
        changed = false;
        pass++;

        vector<pair<int,int>> toRemove;

        // Scan entire grid
        for (int r = 0; r < grid.size(); r++) {
            for (int c = 0; c < grid[r].size(); c++) {
                if (grid[r][c] == '@') {
                    int neighbors = countNeighbors(grid, r, c);
                    if (neighbors < 4) {
                        toRemove.push_back({r, c});
                    }
                }
            }
        }

        // Apply removals only after full pass
        if (!toRemove.empty()) {
            changed = true;
            totalRemoved += toRemove.size();
            for (auto& pos : toRemove) {
                grid[pos.first][pos.second] = '.';
            }
        }

        cout << "Pass " << pass << " removed " << toRemove.size() << " cells." << endl;
    }

    cout << "\nFinal stabilized grid:" << endl;
    for (auto& row : grid) {
        cout << row << endl;
    }

    cout << "\nTotal '@' cells removed: " << totalRemoved << endl;
    cout << "No more removals possible in final revision." << endl;

    return 0;
}
