cmake_minimum_required(VERSION 3.2.2)
project(FuseCam)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH}
        "${CMAKE_SOURCE_DIR}/cmake/")

set(CMAKE_CXX_STANDARD 11)

find_package(FUSE REQUIRED)
include_directories(${FUSE_INCLUDE_DIR})
link_libraries(${FUSE_LIBRARIES})

set(SOURCE_FILES
        main.cpp
        Router.cpp Router.h
        Camera.cpp Camera.h
        Io.cpp Io.h
        Stream.cpp Stream.h
        Filter.cpp Filter.h
        Frame.cpp Frame.h)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Werror")
add_definitions(-D_FILE_OFFSET_BITS=64 -DFUSE_USE_VERSION=30)

# Target Dummy
add_definitions(-DVENDOR_DUMMY)
set(DUMMY_SOURCE_FILES ${SOURCE_FILES}
        vendor/Dummy/DummyCamera.h vendor/Dummy/DummyCamera.cpp
        vendor/Dummy/DummyIo.cpp vendor/Dummy/DummyIo.h
        vendor/Video4Linux/Video4LinuxStream.cpp vendor/Video4Linux/Video4LinuxStream.h)
add_executable(Dummy ${DUMMY_SOURCE_FILES})