#include <iostream>
#include <string>
#include "curl/curl.h"
#include "zlib.h"

int init_curl() {
  CURL *curl;
  curl = curl_easy_init();
  std::cout << "curl - OK" << std::endl;
  z_stream strm;
  std::cout << "zlib - OK" << std::endl;
  return 0;
}
