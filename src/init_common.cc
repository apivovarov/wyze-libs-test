#include <iostream>
#include <string>
#include <nlohmann/json.hpp>
#include "spdlog/spdlog.h"

int init_common() {
  auto j3 = nlohmann::json::parse(R"({"happy": true, "pi": 3.141})");
  std::cout << "nlohmann::json - OK" << std::endl;
  spdlog::info("Welcome to spdlog!", j3.size());
  std::cout << "spdlog - OK" << std::endl;
  return 0;
}
