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

// Process each problem
for (const auto& range : problem_ranges) {
    vector<string> problem_columns;
    // Extract columns for this problem
    for (int col = range.first; col <= range.second; ++col) {
        string col_str;
        for (const auto& l : lines) {
            col_str += l[col];
        }
        problem_columns.push_back(col_str);
    }

    // Transpose columns back to rows for this problem
    // Each row corresponds to a line in the problem
    vector<string> problem_rows(lines.size());
    for (size_t r = 0; r < lines.size(); ++r) {
        for (const auto& col_str : problem_columns) {
            problem_rows[r] += col_str[r];
        }
    }

    // The last row contains the operation symbol (+ or *)
    string op_line = problem_rows.back();
    char op = ' ';
    for (char c : op_line) {
        if (c == '+' || c == '*') {
            op = c;
            break;
        }
    }
    if (op == ' ') {
        cerr << "No operation symbol found in problem." << endl;
        return 1;
    }

    // Extract numbers from all rows except the last
    vector<long long> numbers;
    for (size_t r = 0; r < problem_rows.size() - 1; ++r) {
        string trimmed = trim(problem_rows[r]);
        if (!trimmed.empty()) {
            // Convert trimmed string to number
            istringstream iss(trimmed);
            long long num;
            iss >> num;
            numbers.push_back(num);
        }
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