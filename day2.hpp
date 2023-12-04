#include "day.hpp"

class Day2 : public Day {

public:
    Day2() : Day{"input/day2.txt"} {}
    ~Day2() override = default;

    void run() override {
        // Part 1
        std::map<std::string, int> bag{{"red", 12}, {"green", 13}, {"blue", 14}};
        int sum{};
        bool part1{};
        for (int i{}; i < lines.size(); ++i) {
          auto line = lines[i];
          line = line.substr(line.find(':') + 2, line.size());
          auto subsets = getFromLine(line, "; ");
          std::map<std::string, int> maxCubes{};
          for (const auto& subset : subsets) {
            auto cubes = getFromLine(subset, ", ");
            for (const auto& cube : cubes) {
              auto delim = cube.find(' ');
              auto n = std::stoi(cube.substr(0, delim));
              auto color = cube.substr(delim + 1, cube.size());
              if (part1) {
                if (bag[color] < n) {
                  goto nextgame;
                }
              } else {
                auto& maxN = maxCubes[color];
                maxN = std::max(maxN, n);
              }
            }
          }

          if (part1) {
            sum += i + 1;
          } else {
            sum += maxCubes["red"] * maxCubes["green"] * maxCubes["blue"];
          }
          nextgame:;
        }

        std::cout << sum << std::endl;
    }


};
