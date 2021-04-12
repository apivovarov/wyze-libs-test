#include <iostream>
#include <string>
#include "openssl/ssl.h"

int init_openssl() {
  SSL_load_error_strings();
  SSL_library_init();
  std::cout << "openssl - OK" << std::endl;
  return 0;
}
