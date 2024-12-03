#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>

#define FILE_PATH "input.txt"
#define EOS std::string::npos

enum ParseCode {
  PASS,
  CONTINUE,
  BREAK
};

int countDigits(const std::string &s);

ParseCode parseForNumber(
  const std::string &text,
  const size_t afterToken,
  size_t &from,
  int &number,
  size_t &tokenIndex
);

const std::string MUL = "mul(";
const std::string COMMA = ",";
const std::string END = ")";

int main() {

  std::fstream file(FILE_PATH);
  std::string text;

  // assuming file consist of exactly one line.
  std::getline(file, text);

  size_t from = 0;

  int result = 0;

  for(;;) {
    from = text.find(MUL, from);
    auto afterFrom = from + MUL.length();

    if (from == EOS) {
      break;
    }

    int x = 0;
    size_t indexComma = text.find(COMMA, from);
    auto afterComma = indexComma + COMMA.length();
    ParseCode code = parseForNumber(text, afterFrom, from, x, indexComma);

    if (code == BREAK) {
      break;
    }

    if (code == CONTINUE) {
      continue;
    }

    int y = 0;
    size_t indexEnd = text.find(END, indexComma);
    code = parseForNumber(text, afterComma, from, y, indexEnd);

    if (code == BREAK) {
      break;
    }

    if (code == CONTINUE) {
      continue;
    }

    result += x * y;
    ++from;
  }

  std::cout << result << std::endl;
}

ParseCode parseForNumber(
  const std::string &text,
  const size_t afterToken,
  size_t &from,
  int &number,
  size_t &tokenIndex
) {
  if (tokenIndex == EOS) {
    return BREAK;
  }

  auto length = tokenIndex - afterToken;

  if (!length || length > 3) {
    ++from;
    return CONTINUE;
  }

  std::string numberAsString = text.substr(afterToken, length);

  bool allDigits = countDigits(numberAsString) == length;

  if (!allDigits) {
    from = tokenIndex;
    return CONTINUE;
  }

  number = std::stoi(numberAsString);
  return PASS;
}

int countDigits(const std::string &s) {
  return std::count_if(
    s.begin(),
    s.end(),
    [](unsigned char c) { return std::isdigit(c); }
  );
}
