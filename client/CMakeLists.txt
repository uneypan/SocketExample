cmake_minimum_required(VERSION 3.10)
project(server)

set(CMAKE_CXX_STANDARD 11)

add_executable(client client.cpp)

target_link_libraries(client pthread)
