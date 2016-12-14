cmake_minimum_required(VERSION 3.6)
project(FuseCam)

set(CMAKE_CXX_STANDARD 11)

find_library(FUSE_LIBRARY fuse)

set(SOURCE_FILES main.cpp)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Werror")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${FUSE_DEFINITIONS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DFUSE_USE_VERSION=30")

add_definitions (-D_FILE_OFFSET_BITS=64 -DFUSE_USE_VERSION=26)
add_executable(FuseCam ${SOURCE_FILES})