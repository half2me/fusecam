cmake_minimum_required(VERSION 3.6)
project(FuseCam)

set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH}
        "${CMAKE_SOURCE_DIR}/cmake/")

set(CMAKE_CXX_STANDARD 11)

find_package(FUSE REQUIRED)
include_directories(${FUSE_INCLUDE_DIR})
link_libraries(${FUSE_LIBRARIES})

set(SOURCE_FILES main.cpp Router.cpp Router.h Camera.cpp Camera.h Stream.cpp Stream.h Io.cpp Io.h)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Werror")

add_definitions (-D_FILE_OFFSET_BITS=64 -DFUSE_USE_VERSION=30)
add_executable(FuseCam ${SOURCE_FILES})