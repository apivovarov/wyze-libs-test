#include <iostream>
#include <string>
#include <nlohmann/json.hpp>
#include "spdlog/spdlog.h"
#include "curl/curl.h"
#include "zlib.h"
#include "openssl/ssl.h"

void init_ssl();

int test1() {
  std::cout << "test1" << std::endl;
  auto j3 = nlohmann::json::parse(R"({"happy": true, "pi": 3.141})");
  spdlog::info("Welcome to spdlog!");
  CURL *curl;
  curl = curl_easy_init();
  init_ssl();
  z_stream strm;
  return 0;
}

void init_ssl() {
  SSL_load_error_strings();
  SSL_library_init();
}
