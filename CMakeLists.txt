cmake_minimum_required(VERSION 3.24)
set(CMAKE_CXX_STANDARD 20)

project(
        "MEP"
        VERSION 1.0.0
        LANGUAGES CXX)

add_subdirectory(glfw)
add_subdirectory(glew)

set(CMAKE_PREFIX_PATH "C:/Program Files (x86)/GLFW/lib/cmake/glfw3")
# spdlog version: 1.11.0
# set(SPDLOG_INCLUDE_DIR libs/spdlog/include)
if(NOT TARGET spdlog)
    # Stand-alone build
    find_package(spdlog REQUIRED)
endif()

set(LIBS glfw libglew_static spdlog::spdlog)
message(STATUS ${CMAKE_BUILD_TYPE})

message(STATUS ${LIBS})

set(src
        src/properties/MessageBoard.h
        src/main.cpp)

add_executable(${PROJECT_NAME} ${src})

target_link_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/glfw/include)
target_link_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/glew/include)


target_link_libraries(${PROJECT_NAME} PRIVATE ${LIBS} )