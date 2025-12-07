#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <set>
#include <tuple>

using namespace std;

//Now we want to count how many different ways the beam can split as it goes down the grid.
//number of full paths = the number of leaf nodes in the tree





struct Beam {
    int row, col;
};

int main() {
    // Read input.txt
    ifstream file("input.txt");
    if (!file) {
        cerr << "Error: could not open input.txt" << endl;
        return 1;
    }

    vector<string> grid;
    string line;
    while (getline(file, line)) {
        if (!line.empty()) {
            grid.push_back(line);
        }
    }
    file.close();

    int rows = grid.size();
    int cols = grid[0].size();

    // Find source S
    int startRow = 0, startCol = -1;
    for (int c = 0; c < cols; c++) {
        if (grid[0][c] == 'S') {
            startCol = c;
        }
    }

    queue<Beam> beams;  //create a queue 'beams' as they are processed in FIFO order
    beams.push({startRow, startCol});   //Initially, push the starting beam at the source 'S' position (row 0)

    int times_split = 0;    //keep track of how many times the beam splits

    while (!beams.empty()) {    //while there are active beams:
        Beam b = beams.front();//get the next beam from the queue
        beams.pop();        //remove it from the queue


        //new row (nr) and new column (nc) after moving down
        int nr = b.row + 1; // always move down
        int nc = b.col;

        //if (nr < 0 || nr >= rows || nc < 0 || nc >= cols) continue;

        char cell = grid[nr][nc];   //read what is in the cell

        if (cell == '.') {         
            grid[nr][nc] = '|'; // mark downward beam
            beams.push({nr, nc});   //push a new beam at (nr,nc) so it continues downward in next iteration
        } else if (cell == '^') {
            times_split++;
            // keep ^ visible
            if (nc > 0 && grid[nr][nc-1] == '.') grid[nr][nc-1] = '-';
            if (nc < cols-1 && grid[nr][nc+1] == '.') grid[nr][nc+1] = '-';
            //spawn two new beams to the left and right
            if (nc > 0) beams.push({nr, nc-1});
            if (nc < cols-1) beams.push({nr, nc+1});
        }
    }

    // Print final grid with beam paths
    for (auto &row : grid) {
        //cout << row << endl;
    }

    cout << "Total splits: " << times_split << endl;
    return 0;
}
