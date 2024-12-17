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
int scanDirection(int x, int y, int dx, int dy);

std::map<char, std::vector<Coordinate>> map;
std::set<std::string> antiNodes;

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

  for (auto const &antenna : map) {
    auto coordinates = antenna.second;

    for (decltype(coordinates.size()) i = 0; i < coordinates.size() - 1; ++i) {
      for (decltype(coordinates.size()) j = i + 1; j < coordinates.size(); ++j) {
        std::string key = std::to_string(coordinates[i].x) + '-' + std::to_string(coordinates[i].y);

        if (antiNodes.find(key) == antiNodes.end()) {
          ++count;
          antiNodes.insert(key);
        }

        key = std::to_string(coordinates[j].x) + '-' + std::to_string(coordinates[j].y);

        if (antiNodes.find(key) == antiNodes.end()) {
          ++count;
          antiNodes.insert(key);
        }

        auto deltaX = coordinates[i].x - coordinates[j].x;
        auto deltaY = coordinates[i].y - coordinates[j].y;

        count += scanDirection(coordinates[i].x, coordinates[i].y, deltaX, deltaY);
        count += scanDirection(coordinates[j].x, coordinates[j].y, -deltaX, -deltaY);
      }
    }
  }

  std::cout << count << std::endl;
}

int scanDirection(int x, int y, int dx, int dy) {
  int count = 0;

  for (auto p1X = x + dx, p1Y = y + dy; inBounds(p1Y, p1X); p1X += dx, p1Y += dy) {
    std::string key = std::to_string(p1X) + '-' + std::to_string(p1Y);

    if (antiNodes.find(key) == antiNodes.end()) {
      ++count;
      antiNodes.insert(key);
    }
  }

  return count;
}

bool inBounds(size_t i, size_t j) {
  return i >= 0 && i < h
   && j >= 0 && j < w;
}
