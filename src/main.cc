#include <vector>
#include <algorithm>
#include <iostream>

int init_common();
int init_absl();
int init_curl();
int init_aws();
int close_aws();
int init_s3(const char* s3_region, const char* TAG);
int init_transfer();
int init_sagemaker(const char* s3_region, char const* profile);

int main() {
  std::vector<int> nums{3, 4, 2, 8, 15, 267};
  auto print = [](const int& n) { std::cout << " " << n; };
 
  std::cout << "std::for_each:";
  std::for_each(nums.cbegin(), nums.cend(), print);
  std::cout << '\n';

  init_common();
  init_absl();
  init_curl();
  init_aws();
  init_s3("us-west-1", "default");
  init_transfer();
  init_sagemaker("us-west-1", "default");
  close_aws();
  return 0;
}
