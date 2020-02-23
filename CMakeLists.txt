cmake_minimum_required(VERSION 3.10)

project(hello-triangle)

set(CMAKE_CXX_STANDARD 11)

add_executable(hello-triangle main.cpp)

add_subdirectory(libs/glapp)
target_link_libraries(hello-triangle glapp)