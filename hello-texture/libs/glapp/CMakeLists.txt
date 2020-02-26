add_library(glapp
    src/glapp.cpp
    src/shader.cpp
)

target_include_directories(glapp PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include" "/usr/local/include")
target_link_directories(glapp PUBLIC "/usr/local/lib")
target_link_libraries(glapp GLEW glfw.3.3)
if (APPLE)
  target_link_libraries(glapp "-framework OpenGL")
endif()