# FILEPATH: /Users/uneypan/Desktop/SocketExample/client/CMakeLists.txt
cmake_minimum_required(VERSION 3.10)
project(client)

set(CMAKE_CXX_STANDARD 11)

# Add the directory containing cJSON.cpp to the include path
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# Add the source files to the executable
add_executable(client client.cpp cJSON.c)

# Link the pthread library
target_link_libraries(client pthread)
