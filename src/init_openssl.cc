#include "openssl/ssl.h"

int init_openssl() {
  SSL_load_error_strings();
  SSL_library_init();
  return 0;
}
