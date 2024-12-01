#include <fstream>
#include <vector>
#include <algorithm>
#include <iostream>
#include <map>

#define FILE_PATH "input.txt"

int main() {
  std::ifstream file(FILE_PATH);
  std::vector<int> left;
  std::map<int, int> right;

  int current = 0;

  while (file >> current) {
    left.push_back(current);

    file >> current;
    right[current]++;
  }

  int result = 0;

  for (const auto i : left) {
    result += i * right[i];
  }

  std::cout << result << std::endl;
}
