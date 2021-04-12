int init_common();
int init_absl();
int init_curl();
int init_aws();
int close_aws();
int init_s3(const char* s3_region, const char* TAG);
int init_transfer();
int init_sagemaker(const char* s3_region, char const* profile);

int main() {
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
