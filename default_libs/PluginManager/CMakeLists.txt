cmake_minimum_required(VERSION 3.22.1)
set(CMAKE_CXX_STANDARD 20)

project(
        "PluginManager"
        VERSION 1.0.0
        LANGUAGES CXX)

set(src
        PluginManager/PluginManager.cpp
)

add_library(${PROJECT_NAME} SHARED
        ${src}
)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})