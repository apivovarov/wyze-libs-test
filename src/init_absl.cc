#include <iostream>
#include <string>
#include <absl/strings/str_split.h>

int init_absl() {
  std::vector<std::string> v = absl::StrSplit("a,b,,c", ',');
  std::cout << "absl - OK" << std::endl;
  return 0;
}
