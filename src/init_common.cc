#include <iostream>
#include <string>
#include <nlohmann/json.hpp>
#include "spdlog/spdlog.h"

int init_common_libs() {
  std::cout << "test1" << std::endl;
  auto j3 = nlohmann::json::parse(R"({"happy": true, "pi": 3.141})");
  spdlog::info("Welcome to spdlog!", j3.size());
  return 0;
}
