cmake_minimum_required(VERSION 3.3)
project(RoadINS)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(D:/work/lib/googletest-master/googletest/include D:/work/lib/boost_1_59_0)

set(SOURCE_FILES src/main.cpp src/network/Node.h src/network/Road.h src/io/DataReader.cpp src/io/DataReader.h src/network/Node.cpp src/network/Node.cpp src/network/Node.h src/network/Road.cpp src/algorithm/Dijkstra.cpp src/algorithm/Dijkstra.h src/util/TimePrinter.cpp src/util/TimePrinter.h src/network/Trajectory.cpp src/network/Trajectory.h test/trajectory_test.cpp src/network/TrajectoryConstructor.cpp src/network/TrajectoryConstructor.h test/test_fixture.h test/test_fixture.cpp test/top_k_test.cpp src/algorithm/INS.cpp src/algorithm/INS.h src/util/ptr_node_comp.h src/network/RoadNetwork.cpp src/network/RoadNetwork.h src/util/ptr_node_comp.cpp src/algorithm/MknnProcessor.h src/algorithm/VStar.cpp src/algorithm/VStar.h test/experiment.cpp test/experiment_multi.cpp)

aux_source_directory(test DIR_TEST)

add_executable(RoadINS ${SOURCE_FILES} ${DIR_TEST})

target_link_libraries(RoadINS D:/work/lib/googletest-master/googletest/lib/libgtest.a D:/work/lib/boost_1_59_0/stage/lib/libboost_timer-mgw52-mt-d-1_59.a  D:/work/lib/boost_1_59_0/stage/lib/libboost_chrono-mgw52-mt-d-1_59.a  D:/work/lib/boost_1_59_0/stage/lib/libboost_system-mgw52-mt-d-1_59.a)
