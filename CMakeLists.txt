cmake_minimum_required(VERSION 3.24.1)
set(CMAKE_CXX_STANDARD 20)

project(
        "MEP"
        VERSION 1.0.0
        LANGUAGES CXX)

add_subdirectory(libs/glfw)
add_subdirectory(libs/glew)
add_subdirectory(libs/glm)

# spdlog version: 1.11.0
# set(SPDLOG_INCLUDE_DIR libs/spdlog/include)
if(NOT TARGET spdlog)
    # Stand-alone build
    find_package(spdlog REQUIRED)
endif()

set(LIBS glfw libglew_static glm spdlog::spdlog)
message(STATUS ${CMAKE_BUILD_TYPE})

message(STATUS ${LIBS})

set(src
        src/Game/Graphics/Shaders/Shader.cpp
        src/Game/Graphics/Shaders/Shader.h
        src/Game/InternalLogger.cpp
        src/Game/InternalLogger.h
        src/properties/MessageBoard.h
        src/main.cpp src/Game/Graphics/VBO/VBO.cpp src/Game/Graphics/VBO/VBO.h src/Game/Graphics/EBO/EBO.cpp src/Game/Graphics/EBO/EBO.h src/Game/Graphics/VAO/VAO.cpp src/Game/Graphics/VAO/VAO.h)

add_executable(${PROJECT_NAME} ${src})

target_link_directories(${PROJECT_NAME} PUBLIC libs/glfw/include)
target_link_directories(${PROJECT_NAME} PUBLIC libs/glew/include)


target_link_libraries(${PROJECT_NAME} PRIVATE ${LIBS} )