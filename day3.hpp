#include "day.hpp"

class Day3 : public Day {

public:
    Day3() : Day{"input/day3.txt"} {}
    ~Day3() override = default;

    void run() override {
        // Part 1
      uint64_t sum{};
      std::map<std::pair<int, int>, std::vector<uint64_t>> gearMap{};
      for (int i{}; i < lines.size(); ++i) {
        uint64_t partNumber{};
        bool isPart{}, isGear{};
        std::pair<int, int> gearCoords{};
        for (int j{}; j < lines[i].size(); ++j) {
          if (std::isdigit(lines[i][j])) {
            partNumber *= 10;
            partNumber += std::stoull(std::string{lines[i][j]});
            isPart |= isPartNumber(i, j);
            auto coords = isGearNumber(i, j);
            if (coords.first != -1 && coords.second != -1) {
              isGear = true;
              gearCoords = coords;
            }
          } else {
            sum += isPart ? partNumber : 0;
            if (isGear) {
              gearMap[gearCoords].push_back(partNumber);
            }
            partNumber = 0;
            isPart = false;
            isGear = false;
          }
        }
        sum += isPart ? partNumber : 0;
        if (isGear) {
          gearMap[gearCoords].push_back(partNumber);
        }
      }

      std::cout << sum << std::endl;

      // Part 2
      sum = 0;
      for (const auto& [coord, partNumbers] : gearMap) {
        if (partNumbers.size() == 2) {
          sum += partNumbers[0] * partNumbers[1];
        }
      }

      std::cout << sum << std::endl;
    }

    std::pair<int, int> isGearNumber(int i, int j) {
      for (int y = std::max(i - 1, 0); y <= std::min(i + 1,(int)lines.size() - 1); ++y) {
        for (int x = std::max(j - 1, 0); x <= std::min(j + 1,(int)lines[i].size() - 1); ++x) {
          if (lines[y][x] == '*') {
            return std::make_pair(y, x);
          }
        }
      }

      return std::make_pair(-1, -1);
    }

    bool isPartNumber(int i, int j) {
      for (int y = std::max(i - 1, 0); y <= std::min(i + 1,(int)lines.size() - 1); ++y) {
        for (int x = std::max(j - 1, 0); x <= std::min(j + 1,(int)lines[i].size() - 1); ++x) {
          if (lines[y][x] != '.' && !std::isdigit(lines[y][x])) {
            return true;
          }
        }
      }

      return false;
    }

};
