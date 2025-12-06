#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

struct Range {
  long long start;
  long long end;

};

int main() {
    std::ifstream file("input.txt");
    if (!file) {
        std::cerr << "Could not open input.txt\n";
        return 1;
    }

    std::vector<Range> ranges;
    std::string line;

    // Read only the first section (ranges)
    while (std::getline(file, line)) {
        if (line.empty()) break; // stop at blank line
        auto dashPos = line.find('-');
        if (dashPos != std::string::npos) {
            long long start = std::stoll(line.substr(0, dashPos));
            long long end   = std::stoll(line.substr(dashPos+1));
            ranges.push_back({start, end});
        }
    }

    // Sort ranges by start
    std::sort(ranges.begin(), ranges.end(),
              [](const Range& a, const Range& b) {
                  return a.start < b.start;
              });

    // Merge overlapping ranges
    std::vector<Range> merged;
    for (const auto& r : ranges) {
        if (merged.empty() || r.start > merged.back().end + 1) {
            merged.push_back(r);
        } else {
            merged.back().end = std::max(merged.back().end, r.end);
        }
    }

  long long total_unique = 0;
  for (const auto &r : merged) {
    total_unique += (r.end - r.start + 1);
   

  }
  cout << "Total unique numbers in ranges: " << total_unique << endl;
}

