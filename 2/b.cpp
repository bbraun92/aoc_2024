#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include <vector>

#define FILE_PATH "input.txt"

bool isReportSafe(const std::vector<int> &report, bool dampened = false);

int main() {

  std::string line;
  std::ifstream file(FILE_PATH);

  int safeCount = 0;

  while (std::getline(file, line)) {
    std::istringstream lineStream{line};
    std::vector<int> report{std::istream_iterator<int>(lineStream), std::istream_iterator<int>()};

    if (isReportSafe(report)) {
      ++safeCount;
    }
  }

  std::cout << safeCount << std::endl;
}

bool isReportSafe(const std::vector<int> &report, bool dampened) {
  bool increasing = false, decreasing = false;
  
  for (decltype(report.size()) current = 0; current < report.size() - 1; ++current) {
    decltype(report.size()) next = current + 1;

    int currentLevel = report[current];
    int nextLevel = report[next];

    increasing = increasing || nextLevel > currentLevel;
    decreasing = decreasing || currentLevel > nextLevel;

    int diff = abs(nextLevel - currentLevel);

    if ((increasing && decreasing) || (diff < 1 || diff > 3)) {
      if (!dampened) {
        dampened = true;
  
        std::vector<int> candidateA = report;
        std::vector<int> candidateB = report;
        std::vector<int> candidateC = report;

        candidateA.erase(candidateA.cbegin() + current);
        candidateB.erase(candidateB.cbegin() + next);
        candidateC.erase(candidateC.cbegin());

        return isReportSafe(candidateA, true) || isReportSafe(candidateB, true) || isReportSafe(candidateC, true);
      } else {
        return false;
      }
    }
  }

  return true;
}
