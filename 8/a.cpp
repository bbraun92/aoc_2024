#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

#define FILE_PATH "input.txt"

struct Coordinate {
  size_t x;
  size_t y;
};

bool inBounds(size_t i, size_t j);

std::map<char, std::vector<Coordinate>> map;

size_t w = 0;
size_t h = 0;

int main() {
  std::ifstream file(FILE_PATH);
  std::string line;

  // read file into map.
  for (; std::getline(file, line); ++h) {
    for (decltype(line.length()) j = 0; j < line.length(); ++j) {
      if ('.' == line[j]) continue;
      map[line[j]].push_back({j, h});
    }
  }

  w = line.length();

  // solve.
  int count = 0;
  std::set<std::string> antiNodes;

  for (auto const &antenna : map) {
    auto coordinates = antenna.second;

    for (decltype(coordinates.size()) i = 0; i < coordinates.size() - 1; ++i) {
      for (decltype(coordinates.size()) j = i + 1; j < coordinates.size(); ++j) {
        auto deltaX = coordinates[i].x - coordinates[j].x;
        auto deltaY = coordinates[i].y - coordinates[j].y;

        auto p1X = coordinates[i].x + deltaX;
        auto p1Y = coordinates[i].y + deltaY;

        if (inBounds(p1Y, p1X)) {
          std::string key = std::to_string(p1X) + '-' + std::to_string(p1Y);
          if (antiNodes.find(key) == antiNodes.end()) {
            ++count;
            antiNodes.insert(key);
          }
        }

        auto p2X = coordinates[j].x - deltaX;
        auto p2Y = coordinates[j].y - deltaY;

        if (inBounds(p2Y, p2X)) {
          std::string key = std::to_string(p2X) + '-' + std::to_string(p2Y);
          if (antiNodes.find(key) == antiNodes.end()) {
            ++count;
            antiNodes.insert(key);
          }
        }
      }
    }
  }

  std::cout << count << std::endl;
}

bool inBounds(size_t i, size_t j) {
  return i >= 0 && i < h
   && j >= 0 && j < w;
}
