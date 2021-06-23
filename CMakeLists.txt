# cmake_minimum_required(VERSION <specify CMake version here>)
project(ant)

set(CMAKE_CXX_STANDARD 14)

add_executable(client src/client.cpp)
add_executable(server src/server.cpp)
