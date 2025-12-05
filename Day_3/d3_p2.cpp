#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

std::string highest_n_digit_number(const std::string &s, int n) {
    int to_remove = s.size() - n;
    std::vector<char> stack;

    for (char c : s) {
        while (!stack.empty() && to_remove > 0 && stack.back() < c) {
            stack.pop_back();
            to_remove--;
        }
        stack.push_back(c);
    }

    // If we didn’t remove enough, trim from the end
    while ((int)stack.size() > n) {
        stack.pop_back();
    }

    return std::string(stack.begin(), stack.end());
}

int main() {
    std::string bb;
    long long total_battery = 0;

    while (std::cin >> bb) {
        std::cout << "Batterybank as a string: " << bb << std::endl;

        std::string best = highest_n_digit_number(bb, 12);
        long long battery_max = std::stoll(best);

        std::cout << "Battery max as integer: " << battery_max << std::endl;
        total_battery += battery_max;
    }

    std::cout << "\nFinal total: " << total_battery << std::endl;
    return 0;
}
