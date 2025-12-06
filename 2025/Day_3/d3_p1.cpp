#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

// Recursive function to get the highest n-digit number
std::string highest_n_digit_number(const std::string &s, int n) {
    if (n == 0) return "";
    if (n == 1) {
        // Just return the maximum digit in the string
        char max_digit = *std::max_element(s.begin(), s.end());
        return std::string(1, max_digit);
    }

    // Find the maximum digit that leaves enough room for the rest
    char max_digit = '0';
    int pos = -1;
    for (int i = 0; i <= (int)s.size() - n; i++) {
        if (s[i] > max_digit) {
            max_digit = s[i];
            pos = i;
        }
    }

    // Recurse on the substring to the right
    return std::string(1, max_digit) + highest_n_digit_number(s.substr(pos + 1), n - 1);
}

int main() {
    std::string bb;
    int total_battery = 0;

    while (std::cin >> bb) {
        std::cout << "Batterybank as a string: " << bb << std::endl;

        // Use the recursive function to get the best 2-digit number
        std::string best = highest_n_digit_number(bb, 2);
        int battery_max = std::stoi(best);

        std::cout << "Battery max as integer: " << battery_max << std::endl;
        total_battery += battery_max;
    }

    std::cout << "\nFinal total: " << total_battery << std::endl;
    return 0;
}
