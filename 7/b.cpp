#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#define FILE_PATH "input.txt"

enum Operator {
  ADD,
  MULT,
  CONCAT
};

long long evaluate(long long x, long long y, Operator op);
bool recursive(long long solution, long long intermediate, const std::vector<int> &operands, size_t at);

int main() {
  std::ifstream file(FILE_PATH);

  std::string line;

  std::vector<long long> results;
  std::vector<std::vector<int>> operands;

  // read file.
  while (std::getline(file, line)) {
    std::stringstream stream(line);

    long long result;

    stream >> result;

    results.push_back(result);

    // skip :
    stream.get();

    std::vector<int> currentOperands;

    int currentOperand;

    while (stream >> currentOperand) {
      currentOperands.push_back(currentOperand);
    }

    operands.push_back(currentOperands);
  }

  long long sum = 0;

  // solve.
  for (size_t i = 0; i < results.size(); ++i) {
    if (recursive(results[i], 0, operands[i], 0)) {
      sum += results[i];
    }
  }

  std::cout << sum << std::endl;
}

bool recursive(long long solution, long long intermediate, const std::vector<int> &operands, size_t at) {
  
  if (at == operands.size()) {
    return false;
  }

  long long multIntermediate = intermediate == 0 && at == 0 ? operands[at] : evaluate(intermediate, operands[at], MULT);
  long long addIntermediate = evaluate(intermediate, operands[at], ADD);
  long long concatIntermediate = evaluate(intermediate, operands[at], CONCAT);

  if (at == operands.size() - 1) {
    return multIntermediate == solution || addIntermediate == solution || concatIntermediate == solution;
  }

  return recursive(solution, multIntermediate, operands, at + 1) || 
    recursive(solution, addIntermediate, operands, at + 1) ||
    recursive(solution, concatIntermediate, operands, at + 1);
}

long long evaluate(long long x, long long y, Operator op) {
  switch(op) {
    case ADD:
      return x + y;
    case MULT:
      return x * y;
    case CONCAT:
      return std::stoll(std::to_string(x) + std::to_string(y));
  }
}
