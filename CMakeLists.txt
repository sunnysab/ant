cmake_minimum_required(VERSION 3.19)
project(ant)

set(CMAKE_CXX_STANDARD 20)

# Include files
include_directories(src)

# Google Test Configures
add_subdirectory(lib/googletest)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

# Application targets
add_executable(client src/client.cpp)
add_executable(server src/server.cpp)
add_executable(hryC test/hryClient.cpp)
add_executable(hryS test/hryServer.cpp)

# Unit test targets
add_executable(UdpSocketTest test/UdpSocketTest.cpp src/UdpSocket.cpp)
target_link_libraries(UdpSocketTest gtest gtest_main ws2_32)
