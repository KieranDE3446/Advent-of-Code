#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;
// Input is a list of ingrediant IDs
// Consisting of list of fresh ingredient ID ranges,
// a blank line
// and a list of available ingredient IDs
//
// EX:
// 3-5
// 10-14
// 16-20
// 12-18
//
// 1
// 5
// 8
// 11
// 17
// 32
//
// ranges are inclusive
// ingredient is fresh if it is in any ranges
// count the number of fresh ingredients

// thinking
// We want a vector of vectors
// Then just iterate though each element's vector to check if within the ranges
//
//
// Define range type

struct Range {
  long long start;
  long long end;

  // check if a number is inside this range
  bool contains(long long x) const {
    return x >= start && x <= end; // inclusive
  }
};

int main() {
  ifstream file("input.txt");
  int in_range_count = 0;

  // vector of vectors
  vector<Range> ranges;
  vector<long long> numbers;
  string line;
  bool readingRanges = true;

  while (getline(file, line)) {
    if (line.empty()) {
      readingRanges = false;
      continue;
    }
    if (readingRanges) {
      replace(line.begin(), line.end(), '-', ' ');
      istringstream iss(line);
      long long start, end;
      if (iss >> start >> end) {
        ranges.push_back({start, end});
      }
    } else {
      long long num;
      istringstream iss(line);
      if (iss >> num) {
        numbers.push_back(num);
      }
    }
  }

  for (long long n : numbers) {
    bool found = false;
    for (const auto &r : ranges)
      if (r.contains(n)) {
        cout << n << " is in [" << r.start << "," << r.end << "]\n";
        found = true;
        in_range_count++;
        cout << "Number of fresh ingredients: " << in_range_count << endl;
        break;
      }
    if (!found) {
      cout << n << " is not in any range\n";
    }
  }
}
