#include <iostream>
#include <string>
#include "curl/curl.h"
#include "zlib.h"

int init_curl() {
  CURL *curl;
  curl = curl_easy_init();
  z_stream strm;
  return 0;
}
