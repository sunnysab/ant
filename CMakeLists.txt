cmake_minimum_required(VERSION 3.19)
project(ant)

set(CMAKE_CXX_STANDARD 20)

# Include files
include_directories(src)

# Google Test Configures
add_subdirectory(lib/googletest)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})


## Progress Bar Component
add_subdirectory(lib/progress_bar)
include_directories(lib/progress_bar/include)

set(ProtocolFiles
        src/protocol/Frame.cpp
        src/protocol/RequestPayload.cpp
        src/protocol/DataPayload.cpp
        src/protocol/RecvResponse.cpp
        src/protocol/VecStream.cpp)


# Application targets
add_executable(client src/main/client.cpp
        src/UdpSocket.cpp
        src/AntClient.cpp
        src/ReadBuffer.cpp
        ${ProtocolFiles})
add_executable(server src/main/server.cpp
        src/UdpSocket.cpp
        src/AntServer.cpp
        src/ReadBuffer.cpp
        ${ProtocolFiles})
target_link_libraries(client ws2_32)
target_link_libraries(server ws2_32)

# Unit test targets
add_executable(UdpSocketTest
        test/UdpSocketTest.cpp
        src/UdpSocket.cpp)
add_executable(VecStreamTest
        test/VecStreamTest.cpp
        ${ProtocolFiles})
add_executable(PayloadTest
        test/PayloadTest.cpp
        ${ProtocolFiles})
add_executable(DataFrameTest
        test/FrameTest.cpp
        ${ProtocolFiles})
add_executable(ReadBufferTest
        src/ReadBuffer.cpp
        src/WriteBuffer.cpp
        test/BufferTest.cpp)
target_link_libraries(UdpSocketTest gtest gtest_main ws2_32)
target_link_libraries(VecStreamTest gtest gtest_main)
target_link_libraries(PayloadTest gtest gtest_main)
target_link_libraries(DataFrameTest gtest gtest_main)
target_link_libraries(ReadBufferTest gtest gtest_main)