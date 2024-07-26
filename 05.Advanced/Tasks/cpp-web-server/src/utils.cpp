#include "../includes/utils.h"
#include <fstream>
#include <sstream>

std::string readFile(const std::string &filePath) {
  std::ifstream file(filePath);
  std::stringstream buffer;
  buffer << file.rdbuf();
  return buffer.str();
}
