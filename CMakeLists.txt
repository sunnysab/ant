cmake_minimum_required(VERSION 3.19)
project(ant)

set(CMAKE_CXX_STANDARD 20)

# Include files
include_directories(src)

# Google Test Configures
add_subdirectory(lib/googletest)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

# Application targets
add_executable(client src/main/client.cpp
        src/UdpSocket.cpp
        src/AntClient.cpp
        src/protocol/Protocol.cpp)
add_executable(server src/main/server.cpp
        src/UdpSocket.cpp
        src/AntServer.cpp
        src/protocol/Protocol.cpp)
target_link_libraries(client ws2_32)
target_link_libraries(server ws2_32)

# Unit test targets
add_executable(UdpSocketTest test/UdpSocketTest.cpp src/UdpSocket.cpp)
add_executable(VecStreamTest test/VecStreamTest.cpp src/protocol/VecStream.cpp)
target_link_libraries(UdpSocketTest gtest gtest_main ws2_32)
target_link_libraries(VecStreamTest gtest gtest_main)