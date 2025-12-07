#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

using int64 = long long;

int R, C;
vector<string> grid;
vector<vector<int64>> memo;

// Count timelines from position (r, c)
int64 dfs(int r, int c) {



    // Off bottom → valid timeline
    if (r == R)
        return 1;

    if (memo[r][c] != -1)
        return memo[r][c];

    char cell = grid[r][c];
    int64 ways = 0;

    if (cell == '.' || cell == 'S') {
        // continue downward
        ways = dfs(r + 1, c);
    }
    else if (cell == '^') {
        // split: left branch + right branch
        ways = dfs(r + 1, c - 1) + dfs(r + 1, c + 1);
    }

    memo[r][c] = ways;
    return ways;
}

int main() {

    ifstream file("input.txt");
    if (!file) {
        cerr << "Error opening input.txt\n";
        return 1;
    }

    string line;
    vector<string> grid_in;
    while (getline(file, line)) {
        if (!line.empty())
            grid_in.push_back(line);
    }
    file.close();

    grid = grid_in;
    R = grid.size();
    C = grid[0].size();

    // find S
    int startC = -1;
    for (int c = 0; c < C; c++) {
        if (grid[0][c] == 'S')
            startC = c;
    }

    memo.assign(R, vector<int64>(C, -1));

    int64 result = dfs(0, startC);

    cout << "Total quantum timelines: " << result << endl;
    return 0;
}
