#include <aws/core/Aws.h>
#include <aws/core/auth/AWSCredentialsProvider.h>
#include <aws/core/client/ClientConfiguration.h>
#include <iostream>
#include <string>

Aws::SDKOptions options;

int init_aws() {
  Aws::InitAPI(options);
  std::cout << "aws Aws::InitAPI - OK" << std::endl;
  return 0;
}

int close_aws() {
  Aws::ShutdownAPI(options);
  std::cout << "aws Aws::ShutdownAPI - OK" << std::endl;
  return 0;
}
