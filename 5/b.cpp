#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

#define FILE_PATH "input.txt"

std::fstream file(FILE_PATH);

std::map<int, std::vector<int>> rules;
std::vector<std::string> pages;

int main() {
  
  bool readingRules = true;
  std::string line;

  // read file.
  while(std::getline(file, line)) {
    if (line.empty()) {
      readingRules = false;
      continue;
    }

    if (readingRules) {
      int left = std::stoi(line.substr(0, 2));
      int right = std::stoi(line.substr(3, 2));

      rules[left].push_back(right);
      continue;
    }

    pages.push_back(line);
  }

  std::vector<size_t> invalidIndices;

  // solve.
  for (decltype(pages.size()) i = 0; i < pages.size(); ++i) {
    std::vector<int> illegalPages;
    bool valid = true;

    for (decltype(pages[i].size()) j = 0; j < pages[i].size(); j += 3) {
      int current = std::stoi(pages[i].substr(j, 2));
      
      auto jAfterSwap = j;

      for (auto after : rules[current]) {
        auto it = std::find(illegalPages.cbegin(), illegalPages.cend(), after);
        
        if (it != illegalPages.cend()) {
          valid = false;

          auto found = std::to_string(*it);
          auto foundIndex = pages[i].find(found);

          while (jAfterSwap > foundIndex) {
            auto f1 = pages[i][jAfterSwap-3];
            auto f2 = pages[i][jAfterSwap-2];

            auto t1 = pages[i][jAfterSwap];
            auto t2 = pages[i][jAfterSwap+1];

            pages[i][jAfterSwap] = f1;
            pages[i][jAfterSwap+1] = f2;

            pages[i][jAfterSwap-3] = t1;
            pages[i][jAfterSwap-2] = t2;

            jAfterSwap -= 3;
          }
        }
      }

      illegalPages.push_back(current);
    }

    if (!valid) {
      invalidIndices.push_back(i);
    }
  }

  int sum = 0;

  for (const auto index : invalidIndices) {
    size_t i = pages[index].size() / 2 - 1;
    sum += std::stoi(pages[index].substr(i, 2));
  }

  std::cout << sum << std::endl;
}
