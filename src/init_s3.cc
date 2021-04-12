#include <aws/core/Aws.h>
#include <aws/core/auth/AWSCredentialsProvider.h>
#include <aws/core/client/ClientConfiguration.h>
#include <aws/s3/S3Client.h>
#include <aws/s3/model/GetObjectRequest.h>
#include <aws/transfer/TransferManager.h>
#include <fstream>
#include <iostream>
#include <string>

std::shared_ptr<Aws::S3::S3Client> s3_client;

int init_s3(const char* s3_region, const char* TAG) {
  Aws::Client::ClientConfiguration config;
  config.region = s3_region;
  std::cout << "aws ClientConfiguration - OK" << std::endl;

  auto credentialsProvider =
      Aws::MakeShared<Aws::Auth::EnvironmentAWSCredentialsProvider>(TAG);
  std::cout << "aws EnvironmentAWSCredentialsProvider - OK" << std::endl;
  s3_client = std::make_shared<Aws::S3::S3Client>(credentialsProvider, config);
  std::cout << "aws S3Client - OK" << std::endl;
  return 0;
}

int init_transfer() {
  Aws::Utils::Threading::DefaultExecutor dex;
  Aws::Transfer::TransferManagerConfiguration transferConfig(&dex);
  transferConfig.s3Client = s3_client;
  std::cout << "aws transfer - OK" << std::endl;
  return 0;
}

int download_file(Aws::S3::S3Client const& client, Aws::String const& bucket,
                  Aws::String const& key, std::string dest_file) {
  Aws::S3::Model::GetObjectRequest request;
  request.WithBucket(bucket).WithKey(key);

  auto outcome = client.GetObject(request);
  if (!outcome.IsSuccess()) {
    printf("ERROR: S3: outcome.IsSuccess is Fasle\n");
    return -1;
  }
  // Get an Aws::IOStream reference to the retrieved file
  auto& retrieved_file = outcome.GetResultWithOwnership().GetBody();

  std::ofstream output_file(dest_file, std::ios::binary);
  output_file << retrieved_file.rdbuf();
  return 0;
}
