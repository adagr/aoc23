#include "day.hpp"

class Day5 : public Day {

public:
    Day5() : Day{"input/day5.txt"} {}
    ~Day5() override = default;

    struct MapType {
        uint64_t destination;
        uint64_t source;
        uint64_t length;
    };

    void run() override {
        // Part 1
        std::vector<uint64_t> seeds{};
        std::vector<std::pair<uint64_t, uint64_t>> seedsPart2{};
        std::map<std::string, bool> readInput{};
        std::map<std::string, std::vector<MapType>> maps{};
        std::vector<std::string> mapNames{"seed-to-soil", "soil-to-fertilizer", "fertilizer-to-wate", "water-to-light", "light-to-temperature", "temperature-to-humidity", "humidity-to-location"};
        for (const auto& line : lines) {
            if (line == "") {
                for (auto& [key, value] : readInput) {
                    value = false;
                }
            } else  {
                for (const auto& name : mapNames) {
                    if (readInput[name]) {
                        auto data = getNumbersInLine<uint64_t>(line, ' ');
                        maps[name].push_back(MapType{data[0], data[1], data[2]});
                        break;
                    }
                }
            }

            if (line.find("seeds") != std::string::npos) {
                seeds = getNumbersInLine<uint64_t>(line.substr(line.find(": ") + 2, line.size()), ' ');
                for (int i{}; i < seeds.size(); i += 2) {
                    seedsPart2.push_back(std::make_pair(seeds[i], seeds[i + 1]));
                }
            } else {
                for (const auto& name : mapNames) { 
                    if (line.find(name) != std::string::npos) {
                        readInput[name] = true;
                        break;
                    }
                }
            }
        }

        std::vector<uint64_t> locations{};
        for (const auto& seed : seeds) {
            uint64_t location{seed};
            for (const auto& name : mapNames) {
                updateLocation(location, maps[name]);
            }
            locations.push_back(location);
        }
        std::sort(locations.begin(), locations.end());
        std::cout << locations[0] << std::endl;

        //Part2
        for (const auto& [seedStart, seedRange] : seedsPart2) {
            std::vector<std::pair<uint64_t, uint64_t>> locations{std::make_pair(seedStart, seedRange)};
        }
    }

    void updateLocation(uint64_t& location, const std::vector<MapType> mep) {
        for (const auto& data : mep) {
            if (location >= data.source && location <= data.source + data.length) {
                location = data.destination + (location - data.source);
                break;
            }
        }
    }
};
