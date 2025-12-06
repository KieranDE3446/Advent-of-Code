#include <iostream>
#include <fstream> 
#include <string> 
#include <vector> 
#include <sstream> 
#include <cctype> 
#include <algorithm>

using namespace std;

// Helper function to trim whitespace from both ends of a string 
string trim(const string& s) {
     size_t start = s.find_first_not_of(' ');
      if (start == string::npos) return "";
       size_t end = s.find_last_not_of(' ');
        return s.substr(start, end - start + 1); 
    }

// Helper function to convert a string of digits (MSD at top, LSD at bottom) to a number 
long long cephalopodNumber(const vector<string>& lines, int col) { 
    string numStr; // Read digits top to bottom in the column 
    for (size_t row = 0; row < lines.size() - 1; ++row) { // exclude last row (operator row) 
        char c = lines[row][col]; if (isdigit(c)) { 
            numStr += c; } else if (c == ' ') { 
                // skip spaces 
                } else 
                { // invalid char, ignore or handle 
                    } 
                } // numStr now has digits top to bottom, which is MSD to LSD 
                // Convert to number 
                if (numStr.empty()) return 0; 
                return stoll(numStr); 
            }

int main() { 
    ifstream file("input.txt");
     if (!file) 
     {
         cerr << "Failed to open input.txt" << endl;
          return 1;
         }

vector<string> lines;
string line;

// Read all lines of the worksheet
while (getline(file, line)) {
    if (!line.empty()) {
        lines.push_back(line);
    }
}

if (lines.empty()) {
    cerr << "No input provided." << endl;
    return 1;
}

// Determine the width of the worksheet
size_t width = 0;
for (const auto& l : lines) {
    if (l.size() > width) width = l.size();
}

// Pad all lines to the same width
for (auto& l : lines) {
    if (l.size() < width) {
        l += string(width - l.size(), ' ');
    }
}

// Identify problem boundaries by columns that are all spaces
vector<pair<int,int>> problem_ranges;
bool in_problem = false;
int start_col = 0;

for (size_t col = 0; col < width; ++col) {
    bool all_space = true;
    for (const auto& l : lines) {
        if (l[col] != ' ') {
            all_space = false;
            break;
        }
    }

    if (!all_space && !in_problem) {
        in_problem = true;
        start_col = col;
    } else if (all_space && in_problem) {
        in_problem = false;
        problem_ranges.emplace_back(start_col, col - 1);
    }
}
// If last problem goes to the end
if (in_problem) {
    problem_ranges.emplace_back(start_col, width - 1);
}

long long grand_total = 0;

// Process problems right-to-left
for (auto it = problem_ranges.rbegin(); it != problem_ranges.rend(); ++it) {
    int start = it->first;
    int end = it->second;

    // Extract columns for this problem
    vector<int> cols;
    for (int c = start; c <= end; ++c) {
        cols.push_back(c);
    }

    // The operator is at the bottom row, somewhere in these columns
    char op = ' ';
    for (int c : cols) {
        char candidate = lines.back()[c];
        if (candidate == '+' || candidate == '*') {
            op = candidate;
            break;
        }
    }
    if (op == ' ') {
        cerr << "No operation symbol found in problem." << endl;
        return 1;
    }

    // Extract numbers by reading each column top to bottom (MSD to LSD)
    vector<long long> numbers;
    for (int c : cols) {
        long long num = cephalopodNumber(lines, c);
        numbers.push_back(num);
    }

    // Compute the result for this problem
    long long result = (op == '+') ? 0 : 1;
    for (auto n : numbers) {
        if (op == '+') result += n;
        else if (op == '*') result *= n;
    }

    grand_total += result;
}

cout << "Grand total: " << grand_total << endl;

return 0;
}