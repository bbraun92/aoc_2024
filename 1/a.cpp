#include <fstream>
#include <vector>
#include <algorithm>
#include <iostream>

#define FILE_PATH "input.txt"

int main() {
  std::ifstream file(FILE_PATH);
  std::vector<int> left, right;
  
  int current = 0;

  while (file >> current) {
    left.push_back(current);

    file >> current;
    right.push_back(current);
  }

  std::sort(left.begin(), left.end());
  std::sort(right.begin(), right.end());

  int result = 0;
  
  for (decltype(left.size()) i = 0; i < left.size(); ++i) {
    result += abs(left[i] - right[i]);
  }

  std::cout << result << std::endl;
}
