#include <fstream>
#include <string>
#include <sstream>
#include <iostream>

#define FILE_PATH "input.txt"

int main() {

  std::string line;
  std::ifstream file(FILE_PATH);

  int safeCount = 0;

  while (std::getline(file, line)) {
    bool increasing = false, decreasing = false, safe = true;

    std::stringstream ss{line};

    int current = 0, next = 0;
    ss >> current;

    while (ss >> next) {
      increasing = increasing || next > current;
      decreasing = decreasing || current > next;

      int diff = abs(next - current);

      if ((increasing && decreasing) || (diff < 1 || diff > 3)) {
        safe = false;
        break;
      }

      current = next;
    }

    if (safe) {
      ++safeCount;
    }
  }

  std::cout << safeCount << std::endl;
}
