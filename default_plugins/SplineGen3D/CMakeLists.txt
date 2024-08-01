cmake_minimum_required(VERSION 3.22.1)
set(CMAKE_CXX_STANDARD 20)

project(
        "SplineGen3D"
        VERSION 0.4
        LANGUAGES CXX)

set(src
        SplineGen3D/SplineGenerator3D.cpp
)

add_library(${PROJECT_NAME} SHARED ${src})

target_link_libraries(${PROJECT_NAME} PRIVATE PluginManager)

if(WIN32)
    # Example: define WIN32_LEAN_AND_MEAN
    target_compile_definitions(${PROJECT_NAME} PRIVATE WIN32_LEAN_AND_MEAN)
endif()

if(UNIX)
    set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "SplineGen3D")
endif()
