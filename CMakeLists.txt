cmake_minimum_required(VERSION 3.3)
project(RoadINS)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(D:/work/lib/googletest-master/googletest/include)

set(SOURCE_FILES src/main.cpp src/network/Node.h src/network/Road.h src/io/DataReader.cpp src/io/DataReader.h src/network/Node.cpp src/network/Node.cpp src/network/Node.h src/network/Road.cpp src/algorithm/Dijkstra.cpp src/algorithm/Dijkstra.h src/util/TimePrinter.cpp src/util/TimePrinter.h)

aux_source_directory(test DIR_TEST)

add_executable(RoadINS ${SOURCE_FILES} ${DIR_TEST})

target_link_libraries(RoadINS D:/work/lib/googletest-master/googletest/lib/libgtest.a)
