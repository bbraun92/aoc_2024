#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#define FILE_PATH "input.txt"

enum Direction {
  UP,
  RIGHT,
  DOWN,
  LEFT
};

bool inBounds(size_t i, size_t j);
Direction getNewDirection(Direction direction);
void printMap();
void move(size_t &i, size_t &j, Direction d, bool back = false);

std::vector<std::vector<int>> map;

int main() {
  std::fstream file(FILE_PATH);

  std::string line;

  size_t i, j;

  // read file to map matrix.
  while (file >> line) {
    std::vector<int> v;

    // 0 := free, 1 := occupied, 2:= visited
    for (const auto c : line) {
      switch(c) {
        case '.':
          v.push_back(0);
          break;
        case '#':
          v.push_back(1);
          break;
        case '^':
          i = map.size() - 1;
          j = v.size();
          v.push_back(2);
          break;
      }
    }

    map.push_back(v);
  }

  // solve.
  int count = 1;
  Direction direction = UP;

  while(inBounds(i, j)) {
    auto x = map[i][j];

    switch(x) {
      case 0:
        map[i][j] = 2;
        ++count;
        break;
      case 1:
        move(i, j, direction, true);
        direction = getNewDirection(direction);
        break;
      case 2:
      default:
        break;
    }
    
    move(i, j, direction);
  }

  std::cout << count << std::endl;

}

void move(size_t &i, size_t &j, Direction d, bool back) {
  switch(d) {
    size_t step;

    case UP:
      step = back ? 1 : -1;
      i += step;
      break;
    case RIGHT:
      step = back ? -1 : 1;
      j += step;
      break;
    case DOWN:
      step = back ? -1 : 1;
      i += step;
      break;
    case LEFT:
      step = back ? 1 : -1;
      j += step;
      break;
  }
}

Direction getNewDirection(Direction direction) {
  switch (direction) {
    case UP:
      return RIGHT;
    case RIGHT:
      return DOWN;
    case DOWN:
      return LEFT;
    case LEFT:
      return UP;
  }
}

bool inBounds(size_t i, size_t j) {
  return i >= 0 && i < map.size()
   && j >= 0 && j < map[0].size();
}
