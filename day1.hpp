#include "day.hpp"

class Day1 : public Day {

public:
    Day1() : Day{"input/day1.txt"} {}
    ~Day1() override = default;

    void run() override {
        // Part 1
        int sum{};
        std::array<std::string, 9> words = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
        for (const auto& line : lines) {
            int first = -1;
            int second = 0;
            for (int i{}; i < line.size(); ++i) {
                if (std::isdigit(line[i])) {
                    setDigit(first, second, line[i] - '0');
                } else {
                    // Part 2
                    for (int j{}; j < words.size(); ++j) {
                        if (line.substr(i, words[j].size()) == words[j]) {
                            setDigit(first, second, j + 1);
                            break;
                        }
                    }
                }
            }
            std::cout << first * 10 + second << std::endl;
            sum += first * 10 + second;
        }

        std::cout << sum << std::endl;
    }

    void setDigit(int& first, int& second, int d) {
        if (first == -1)
            first = d;
        second = d;
    }

};
