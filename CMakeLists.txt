cmake_minimum_required(VERSION 3.8)

project(wyzetest VERSION 0.3 LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 17)

OPTION (BUILD_SHARED_LIBS "Build shared libraries." ON)
OPTION (POSITION_INDEPENDENT_CODE "add -fPIC" ON)

FILE(GLOB SRC "src/*.cc")
add_library(wyzetest ${SRC})
