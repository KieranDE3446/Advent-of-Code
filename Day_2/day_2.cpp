// Advent of code day 2

#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>
#include <vector>
#include <fstream>
#include <unordered_set>
#include <cstdint>

static std::string u128_to_string(unsigned __int128 x){
    if (x == 0) return std::string("0");
    std::string s;
    while (x > 0) {
        int d = (int)(x % 10);
        s.push_back('0' + d);
        x /= 10;
    }
    std::reverse(s.begin(), s.end());
    return s;
}

int main(int argc, char** argv) {
    // Read multiple ranges from a file (if provided) or stdin (one per line)
    // Each line may contain multiple comma-separated ranges, e.g.
    // 16100064-16192119,2117697596-2117933551,...

    std::string line;
    std::istream* in = &std::cin;
    std::ifstream infile;
    if (argc > 1) {
        infile.open(argv[1]);
        if (!infile) {
            std::cerr << "Failed to open file: " << argv[1] << std::endl;
            return 1;
        }
        in = &infile;
    }

    unsigned long long running_total = 0;
    // Open report file for full results; fall back to stdout if it fails.
    std::ofstream report("full_output.txt");
    std::ostream* detail_out = &report;
    if (!report) detail_out = &std::cout;

    while (std::getline(*in, line)) {
        // Trim whitespace from the line
        line.erase(std::remove_if(line.begin(), line.end(), ::isspace), line.end());
        if (line.empty()) continue;

        size_t pos = 0;
        while (pos < line.size()) {
            size_t comma = line.find(',', pos);
            std::string token;
            if (comma == std::string::npos) {
                token = line.substr(pos);
                pos = line.size();
            } else {
                token = line.substr(pos, comma - pos);
                pos = comma + 1;
            }
            if (token.empty()) continue;

            size_t dashPos = token.find('-');
            if (dashPos == std::string::npos) {
                std::cout << token << ": invalid input" << std::endl;
                continue;
            }

            std::string start_s = token.substr(0, dashPos);
            std::string end_s = token.substr(dashPos + 1);

            // Parse start/end into 64-bit unsigned (inputs are within 64-bit in your dataset)
            auto parse_ull = [&](const std::string &s)->unsigned long long{
                unsigned long long x = 0;
                for (char c : s) {
                    if (c < '0' || c > '9') break;
                    x = x * 10ULL + (unsigned long long)(c - '0');
                }
                return x;
            };

            unsigned long long start = parse_ull(start_s);
            unsigned long long end = parse_ull(end_s);
            if (start > end) std::swap(start, end);

            std::vector<std::string> invalids;
            std::unordered_set<std::string> seen;
            unsigned __int128 invalid_sum = 0;

            int minDigits = (int)start_s.length();
            int maxDigits = (int)end_s.length();

            // Consider all total lengths L between min and max
            for (int L = minDigits; L <= maxDigits; ++L) {
                // For each repetition count r >= 2 that divides L
                for (int r = 2; r <= L; ++r) {
                    if (L % r != 0) continue;
                    int b = L / r; // block length

                    // compute 10^b and 10^L in 128-bit
                    unsigned __int128 pow10b = 1;
                    for (int t = 0; t < b; ++t) pow10b *= 10ULL;
                    unsigned __int128 pow10L = 1;
                    for (int t = 0; t < L; ++t) pow10L *= 10ULL;

                    unsigned __int128 denom = pow10b - 1ULL;
                    if (denom == 0) continue; // safety
                    unsigned __int128 factor = (pow10L - 1ULL) / denom; // geometric series sum

                    unsigned __int128 min_h_digit = (b == 1) ? 1ULL : (pow10b / 10ULL);
                    unsigned __int128 max_h_digit = pow10b - 1ULL;

                    unsigned __int128 h_min = ( ( (unsigned __int128)start + factor - 1ULL) / factor );
                    unsigned __int128 h_max = ( (unsigned __int128)end / factor );

                    if (h_min < min_h_digit) h_min = min_h_digit;
                    if (h_max > max_h_digit) h_max = max_h_digit;
                    if (h_min > h_max) continue;

                    for (unsigned __int128 h = h_min; h <= h_max; ++h) {
                        unsigned __int128 val = h * factor;
                        // convert val to string
                        unsigned __int128 tmp = val;
                        std::string s;
                        if (tmp == 0) s = "0";
                        else {
                            while (tmp > 0) {
                                int digit = (int)(tmp % 10);
                                s.push_back((char)('0' + digit));
                                tmp /= 10;
                            }
                            std::reverse(s.begin(), s.end());
                        }
                        if (s.empty()) continue;
                        if ((int)s.length() != L) continue; // ensure total length L
                        if (seen.insert(s).second) {
                            invalids.push_back(s);
                            invalid_sum += val;
                        }
                    }
                }
            }

            // sort invalids numerically (by length then lexicographic)
            std::sort(invalids.begin(), invalids.end(), [](const std::string &a, const std::string &b){
                if (a.size() != b.size()) return a.size() < b.size();
                return a < b;
            });

            (*detail_out) << token << " invalid IDs:";
            if (invalids.empty()) {
                (*detail_out) << " None";
            } else {
                for (const auto &vs : invalids) (*detail_out) << " " << vs;
            }

            running_total += invalid_sum;
            (*detail_out) << " Sum:" << u128_to_string(invalid_sum) << " Cumulative:" << u128_to_string(running_total) << std::endl;
        }
    }

    if (infile.is_open()) infile.close();
    // Close report (ensure all details written)
    if (report) report.close();

    // Print only the final cumulative total to the console
    std::cout << u128_to_string(running_total) << std::endl;
    return 0;
}