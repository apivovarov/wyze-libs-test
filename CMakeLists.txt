cmake_minimum_required(VERSION 3.8)

project(foo VERSION 0.3 LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 17)

find_package(nlohmann_json 3.9.1 REQUIRED)
find_package(spdlog 1.8.1 REQUIRED)
#find_package(OpenSSL REQUIRED)
#find_package(ZLIB REQUIRED)
find_package(CURL 7.73 REQUIRED)
find_package(aws-cpp-sdk-core REQUIRED)
find_package(aws-cpp-sdk-s3 REQUIRED)
find_package(aws-cpp-sdk-transfer REQUIRED)
find_package(aws-cpp-sdk-sagemaker REQUIRED)
find_package(aws-cpp-sdk-sagemaker-edge REQUIRED)
find_package(gRPC REQUIRED)
#find_package(absl REQUIRED)

# helloworld protobuf library
FILE(GLOB SRC_HW_PB "hw_pb/*.cc")
add_library(hw_pb STATIC ${SRC_HW_PB})
target_include_directories(hw_pb PRIVATE "hw_pb")

# foo executalbe
FILE(GLOB SRC "src/*.cc")
add_executable(foo ${SRC})

target_include_directories(foo PRIVATE "hw_pb")

# Linking hw_pb
target_link_libraries(hw_pb PRIVATE gRPC::grpc++)
target_link_libraries(hw_pb PRIVATE gRPC::grpc++_reflection)

# Linking foo
target_link_libraries(foo PRIVATE hw_pb)
target_link_libraries(foo PRIVATE nlohmann_json::nlohmann_json)
target_link_libraries(foo PRIVATE spdlog::spdlog)
#target_link_libraries(foo PRIVATE OpenSSL::SSL OpenSSL::Crypto)
#target_link_libraries(foo PRIVATE ZLIB::ZLIB)
#target_link_libraries(foo PRIVATE CURL::libcurl)
target_link_libraries(foo PRIVATE aws-cpp-sdk-s3)
target_link_libraries(foo PRIVATE aws-cpp-sdk-transfer)
target_link_libraries(foo PRIVATE aws-cpp-sdk-sagemaker)
target_link_libraries(foo PRIVATE aws-cpp-sdk-sagemaker-edge)
target_link_libraries(foo PRIVATE -static-libstdc++)
target_link_libraries(foo PRIVATE stdc++fs)
