#include <fstream>
#include <map>
#include <stdio.h>
#include <string>
#include <vector>

struct Coordinate {
  size_t x;
  size_t y;
};

struct Direction{
  int x;
  int y;
};

void followTrail(Coordinate position, int height);
bool inBounds(size_t i, size_t j);

const std::vector<Direction> DIRECTIONS{{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

const std::string FILE_PATH = "input.txt";
std::vector<std::vector<int>> map;
std::vector<Coordinate> trailheads;

int currentCount = 0;

int main() {
  std::ifstream file(FILE_PATH);
  std::string line;

  // read file into matrix.
  while (file >> line) {
    std::vector<int> row;

    for (decltype(line.size()) i = 0; i < line.size(); ++i) {
      row.push_back(line[i] - '0');

      if (line[i] == '0') {
        trailheads.push_back({i, map.size()});
      }
    }

    map.push_back(row);
  }

  int count = 0;

  for (const auto &head : trailheads) {
    followTrail(head, 0);
    count += currentCount;
    currentCount = 0;
  }

  printf("%d\n", count);
}

void followTrail(Coordinate position, int height) {
  for (const auto direction : DIRECTIONS) {
    size_t x = position.x + direction.x;
    size_t y = position.y + direction.y;

    if (!inBounds(y, x)) {
      continue;
    }

    int nextHeight = map[y][x];

    if (nextHeight != height + 1) {
      continue;
    }

    if (nextHeight == 9) {
      ++currentCount;
      continue;
    }

    followTrail({x, y}, nextHeight);
  }
}

bool inBounds(size_t i, size_t j) {
  return i >= 0 && i < map.size()
   && j >= 0 && j < map[0].size();
}
