cmake_minimum_required(VERSION 4.0)
project(tanks)

set(CMAKE_CXX_STANDARD 20)

# Add GLAD source
add_library(glad external/glad/src/glad.c)
target_include_directories(glad PUBLIC external/glad/include)

# GLFW paths
set(GLFW_DIR ${CMAKE_SOURCE_DIR}/external/glfw)
include_directories(${GLFW_DIR}/include)

# Point to the actual GLFW lib directory present in the repo
link_directories(${GLFW_DIR}/lib)

add_executable(tanks main.cpp)

add_subdirectory(engine)
target_link_libraries(tanks PRIVATE
        engine
        glad
        glfw3
        opengl32   # Windows OpenGL library
        )
