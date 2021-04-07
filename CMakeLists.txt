cmake_minimum_required(VERSION 3.8)

project(foo VERSION 0.3 LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 17)

OPTION (BUILD_SHARED_LIBS "Build shared libraries." ON)
OPTION (POSITION_INDEPENDENT_CODE "add -fPIC" ON)

find_package(nlohmann_json 3.9.1 REQUIRED)
find_package(spdlog 1.8.1 REQUIRED)
find_package(CURL 7.73 REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(ZLIB REQUIRED)

FILE(GLOB SRC "src/*.cc")
add_library(foo ${SRC})
target_link_libraries(foo PRIVATE nlohmann_json::nlohmann_json)
target_link_libraries(foo PRIVATE spdlog::spdlog)
target_link_libraries(foo PRIVATE ${CURL_LIBRARY})
target_link_libraries(foo PRIVATE OpenSSL::SSL OpenSSL::Crypto)
target_link_libraries(foo PRIVATE ZLIB::ZLIB)


