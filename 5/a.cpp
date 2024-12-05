#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#define FILE_PATH "sample.txt"

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

  std::vector<size_t> validIndices;

  // solve.
  for (decltype(pages.size()) i = 0; i < pages.size(); ++i) {
    std::vector<int> illegalPages;
    bool valid = true;

    for (decltype(pages[i].size()) j = 0; j < pages[i].size(); j += 3) {
      int current = std::stoi(pages[i].substr(j, 2));
      
      for (auto after : rules[current]) {
        auto it = std::find(illegalPages.cbegin(), illegalPages.cend(), after);
        
        if (it != illegalPages.cend()) {
          valid = false;
          illegalPages.push_back(current);
          goto next_page;
        }
      }

      illegalPages.push_back(current);
    }

    next_page:
      if (valid) {
        validIndices.push_back(i);
      }
  }

  int sum = 0;

  for (const auto index : validIndices) {
    size_t i = pages[index].size() / 2 - 1;
    sum += std::stoi(pages[index].substr(i, 2));
  }

  std::cout << sum << std::endl;
}
