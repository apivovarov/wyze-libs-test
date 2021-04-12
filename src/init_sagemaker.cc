#include <aws/core/Aws.h>
#include <aws/core/auth/AWSCredentialsProvider.h>
#include <aws/core/client/ClientConfiguration.h>
#include <aws/core/platform/Environment.h>
#include <aws/sagemaker/SageMakerClient.h>
#include <aws/sagemaker-edge/SagemakerEdgeManagerClient.h>

int init_sagemaker(const char* s3_region, char const* profile) {
    Aws::Client::ClientConfiguration config;
    config.region = s3_region;
    auto credentialsProvider =
        Aws::MakeShared<Aws::Auth::EnvironmentAWSCredentialsProvider>(profile);
  Aws::SageMaker::SageMakerClient sm_client(credentialsProvider, config);
  Aws::SagemakerEdgeManager::SagemakerEdgeManagerClient  sm_edge_client(credentialsProvider, config);
  std::cout << "aws sagemaker - OK" << std::endl;
  return 0;
}
