#include "day.hpp"

class Day4 : public Day {

public:
    Day4() : Day{"input/day4.txt"} {}
    ~Day4() override = default;

    void run() override {
        // Part 1
        int sum{}, totalCards{};
        std::map<int, int> copies{};
        for (int i{}; i  < lines.size(); ++i) {
          auto card = getFromLine(lines[i], ": ")[1];
          auto allNumbers = getFromLine(card, " | ");
          auto winningNumbers = getNumbersInLine(allNumbers[0], ' ');
          auto numbers = getNumbersInLine(allNumbers[1], ' ');
          int points{};
          for (const auto& number : numbers)
            if (contains(winningNumbers, number))
              ++points;

          if (points)
            sum += 1 << (points - 1);

          // Part 2
          for (int j{i + 1}; j < std::min(i + 1 + points, static_cast<int>(lines.size())); ++j)
            copies[j] += copies[i] + 1;

          totalCards += copies[i] + 1;
        }

        std::cout << sum << std::endl;
        std::cout << totalCards << std::endl;
    }

};
