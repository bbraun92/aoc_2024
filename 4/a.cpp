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

bool checkMas(int i, int j, Direction d);

const char LETTERS[3] = {'M', 'A', 'S'};

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
      if (input[i][j] != 'X') continue;

      if (checkMas(i, j, { -1,  0 })) ++count;
      if (checkMas(i, j, { -1,  1 })) ++count;
      if (checkMas(i, j, {  0,  1 })) ++count;
      if (checkMas(i, j, {  1,  1 })) ++count;
      if (checkMas(i, j, {  1,  0 })) ++count;
      if (checkMas(i, j, {  1, -1 })) ++count;
      if (checkMas(i, j, {  0, -1 })) ++count;
      if (checkMas(i, j, { -1, -1 })) ++count;
    }
  }

  std::cout << count << std::endl;
}

bool inBounds(size_t i, size_t j) {
  return i >= 0 && i < input[0].size()
   && j >= 0 && j < input.size();
}

bool checkMas(int i, int j, Direction d) {
  for (int k = 0; k < 3; ++k) {
    auto nextI = i + (k + 1) * d.dI;
    auto nextJ = j + (k + 1) * d.dJ;

    if (!inBounds(nextI, nextJ)) return false;
    if (input[nextI][nextJ] != LETTERS[k]) return false;
  }

  return true;
}
