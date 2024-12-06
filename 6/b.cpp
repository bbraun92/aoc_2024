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

struct Position {
  size_t i;
  size_t j;
};

bool inBounds(size_t i, size_t j);
Direction getNewDirection(Direction direction);
void move(size_t &i, size_t &j, Direction d, bool back = false);

/**
 * @return true Found loop
 * @return false No loop
 */
bool runSimulation(Position start, size_t index);

std::vector<std::vector<int>> map;

int main() {
  std::fstream file(FILE_PATH);

  std::string line;

  Position start;

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
          start.i = map.size() - 1;
          start.j = v.size();
          v.push_back(2);
          break;
      }
    }

    map.push_back(v);
  }

  // solve.
  int count = 0;
  int index = 0;

  auto total = map.size() * map[0].size();

  int pct = 0;

  for (auto &x : map) {
    for (auto &y : x) {
      ++index;

      // Buckle the fuck up, this little maneuver is gonna take us 51 years.
      if (index > total / 100) {
        std::cout << ++pct << "% done." << std::endl;
        index = 0;
      }

      if (y == 2) continue;

      auto temp = y;
      y = 1;

      if(runSimulation(start, index)) {
        ++count;
      }

      y = temp;
    }
  }

  std::cout << count << std::endl;

}

bool runSimulation(Position start, size_t index) {

  Direction direction = UP;

  size_t i = start.i;
  size_t j = start.j;

  bool looped = true;

  std::vector<Position> path;

  while(inBounds(i, j)) {
    auto x = map[i][j];

    switch(x) {
      case 0:
        path.push_back({i, j});
        break;
      case 1:
        move(i, j, direction, true);
        direction = getNewDirection(direction);
        break;
      case 2:
        path.push_back({i, j});
        break;
      default:
        break;
    }    

    if (path.size() < 2) {
      looped = false;
    } else {
      size_t k = path.size() - 1;
      Position last = path[k];
      size_t duplicateIndex = -1;

      // Find first duplicate of last item from the back.
      for (auto x = k - 1; x > path.size() / 2 - 1; --x) {
        Position currPos = path[x];
        
        if (currPos.i == last.i && currPos.j == last.j) {
          duplicateIndex = x;
          break;
        }
      }

      // Using that offset, check if all in between items are the same.
      if (duplicateIndex == -1) {
        looped = false;
      } else {
        size_t diff = k - duplicateIndex;

        looped = true;

        for (auto x = k - 1; x > duplicateIndex; --x) {
          Position currPos = path[x];
          Position offsetPos = path[x-diff];

          if (currPos.i != offsetPos.i || currPos.j != offsetPos.j ) {
            looped = false;
          }
        }
      }
    }

    if (path.size() > 2 && looped) {
      return true;
    }

    move(i, j, direction);
  }

  return false;
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
