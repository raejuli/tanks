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

# Add engine subdirectory first (before executable so glad is available)
add_subdirectory(engine)

add_executable(tanks main.cpp)

target_link_libraries(tanks PRIVATE
        engine
        )

# Copy shaders to build directory
add_custom_command(TARGET tanks POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/shaders
        $<TARGET_FILE_DIR:tanks>/shaders
        COMMENT "Copying shaders to build directory"
)

# Copy textures to build directory
add_custom_command(TARGET tanks POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/textures
        $<TARGET_FILE_DIR:tanks>/textures
        COMMENT "Copying textures to build directory"
)
