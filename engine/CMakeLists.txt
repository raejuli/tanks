cmake_minimum_required(VERSION 4.0)
project(engine)

set(CMAKE_CXX_STANDARD 20)

add_library(engine STATIC
        assets/AssetManager.cpp
        entity/Entity.cpp
        entity/Component.cpp
        )

target_include_directories(engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})