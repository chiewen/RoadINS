cmake_minimum_required(VERSION 3.3)
project(RoadINS)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(D:/work/lib/googletest-master/googletest/include)

set(SOURCE_FILES src/main.cpp src/network/Node.h src/network/Road.h)

add_executable(RoadINS ${SOURCE_FILES})

target_link_libraries(RoadINS D:/work/lib/googletest-master/googletest/lib/libgtest.a)
