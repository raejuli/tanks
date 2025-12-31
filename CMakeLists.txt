cmake_minimum_required(VERSION 4.0)
project(tanks)

set(CMAKE_CXX_STANDARD 20)

add_executable(tanks main.cpp)

add_subdirectory(engine)
target_link_libraries(tanks PRIVATE engine)
