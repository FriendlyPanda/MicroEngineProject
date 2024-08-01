cmake_minimum_required(VERSION 3.22.1)
set(CMAKE_CXX_STANDARD 20)

project(
        "SamplePlugin"
        VERSION 1.0.0
        LANGUAGES CXX)

set(src
        SamplePlugin.cpp
)

message("Generating Sample Plugin 2")

add_library(${PROJECT_NAME} SHARED ${src})

message("${CMAKE_BINARY_DIR}")

set_target_properties(${PROJECT_NAME} PROPERTIES
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
)
target_link_libraries(${PROJECT_NAME} PRIVATE PluginManager)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_INSTALL_PREFIX}/Sample/bin/SamplePlugin.dll)
install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION Sample/bin)

if(WIN32)
    # Example: define WIN32_LEAN_AND_MEAN
    target_compile_definitions(${PROJECT_NAME} PRIVATE WIN32_LEAN_AND_MEAN)
endif()

if(UNIX)
    set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "SamplePlugin")
endif()
