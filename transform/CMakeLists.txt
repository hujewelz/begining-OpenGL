cmake_minimum_required(VERSION 3.10)

project(transform)

set(CMAKE_CXX_STANDARD 11)

add_executable(transform ./src/main.cpp)

add_subdirectory(libs/glapp)
target_link_libraries(transform glapp)

add_subdirectory(libs/image)
target_link_libraries(transform image)

include_directories(glm "${CMAKE_CURRENT_SOURCE_DIR}/libs/glm")