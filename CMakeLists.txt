cmake_minimum_required(VERSION 3.8)

project(foo VERSION 0.3 LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 17)

include(common.cmake)

# Proto file
get_filename_component(hw_proto "protos/helloworld.proto" ABSOLUTE)
get_filename_component(hw_proto_path "${hw_proto}" PATH)

# Generated sources
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/gen)
set(hw_proto_srcs "${CMAKE_CURRENT_BINARY_DIR}/gen/helloworld.pb.cc")
set(hw_proto_hdrs "${CMAKE_CURRENT_BINARY_DIR}/gen/helloworld.pb.h")
set(hw_grpc_srcs "${CMAKE_CURRENT_BINARY_DIR}/gen/helloworld.grpc.pb.cc")
set(hw_grpc_hdrs "${CMAKE_CURRENT_BINARY_DIR}/gen/helloworld.grpc.pb.h")
# It should use protoc from $HOME/aws-install/bin/
add_custom_command(
      OUTPUT "${hw_proto_srcs}" "${hw_proto_hdrs}" "${hw_grpc_srcs}" "${hw_grpc_hdrs}"
      COMMAND ${_PROTOBUF_PROTOC}
      ARGS --grpc_out "${CMAKE_CURRENT_BINARY_DIR}/gen"
        --cpp_out "${CMAKE_CURRENT_BINARY_DIR}/gen"
        -I "${hw_proto_path}"
        --plugin=protoc-gen-grpc="${_GRPC_CPP_PLUGIN_EXECUTABLE}"
        "${hw_proto}"
      DEPENDS "${hw_proto}")

# Include generated *.pb.h files
include_directories("${CMAKE_CURRENT_BINARY_DIR}/gen")

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

# hw_grpc_proto
add_library(hw_grpc_proto
  ${hw_grpc_srcs}
  ${hw_grpc_hdrs}
  ${hw_proto_srcs}
  ${hw_proto_hdrs})
target_link_libraries(hw_grpc_proto gRPC::grpc++ gRPC::grpc++_reflection)

# foo executalbe
FILE(GLOB SRC "src/*.cc")
add_executable(foo ${SRC})

# Linking foo
target_link_libraries(foo PRIVATE hw_grpc_proto)
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
