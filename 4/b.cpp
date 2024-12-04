#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#define FILE_PATH "input.txt"

struct Direction {
  int dI;
  int dJ;
};

std::vector<std::vector<char>> input;

bool inBounds(size_t i, size_t j);

bool checkM(int i, int j, Direction d);
bool checkS(int i, int j, Direction d);

int main() {
  std::fstream file(FILE_PATH);

  // Prepare input matrix (2-dim-vector)
  std::string line;

  while (file >> line) {
    std::vector<char> lineVector;

    for (auto c : line) {
      lineVector.push_back(c);
    }

    input.push_back(lineVector);
  }

  int count = 0;

  // Solve
  for (decltype(input.size()) i = 0; i < input.size(); ++i) {
    for (decltype(input.size()) j = 0; j < input[0].size(); ++j) {
      if (input[i][j] != 'A') continue;

      if ((
          (checkM(i, j, {-1, -1}) && checkS(i, j, {1, 1})) ||
          (checkS(i, j, {-1, -1}) && checkM(i, j, {1, 1}))
        ) && (
          (checkM(i, j, {-1, 1}) && checkS(i, j, {1, -1})) ||
          (checkS(i, j, {-1, 1}) && checkM(i, j, {1, -1}))
        )
      ) ++count;
    }
  }

  std::cout << count << std::endl;
}

bool inBounds(size_t i, size_t j) {
  return i >= 0 && i < input[0].size()
   && j >= 0 && j < input.size();
}

bool checkM(int i, int j, Direction d) {
  
  auto nextI = i + 1 * d.dI;
  auto nextJ = j + 1 * d.dJ;

  return inBounds(nextI, nextJ) &&
    input[nextI][nextJ] == 'M';
}

bool checkS(int i, int j, Direction d) {
  
  auto nextI = i + 1 * d.dI;
  auto nextJ = j + 1 * d.dJ;

  return inBounds(nextI, nextJ) &&
    input[nextI][nextJ] == 'S';
}
