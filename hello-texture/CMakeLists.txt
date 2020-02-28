cmake_minimum_required(VERSION 3.10)

project(hello-texture)

set(CMAKE_CXX_STANDARD 11)

add_executable(hello-texture ./src/main.cpp)

add_subdirectory(libs/glapp)
target_link_libraries(hello-texture glapp)

add_subdirectory(libs/image)
target_link_libraries(hello-texture image)