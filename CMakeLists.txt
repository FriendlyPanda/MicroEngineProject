cmake_minimum_required(VERSION 3.24)
set(CMAKE_CXX_STANDARD 20)

project(
        "MEP"
        VERSION 1.0.0
        LANGUAGES CXX)

# spdlog version: 1.11.0
# set(SPDLOG_INCLUDE_DIR libs/spdlog/include)
if(NOT TARGET spdlog)
    # Stand-alone build
    find_package(spdlog REQUIRED)
endif()
find_package(OpenGL REQUIRED COMPONENTS OpenGL)
find_package(glfw3 REQUIRED)

set(GLM_INCLUDE_DIR E:/DEV/cpp/glm)

include_directories(${GLM_INCLUDE_DIR} ${GLFW3_INCLUDE_DIR})

set(LIBS glfw3 opengl32 spdlog::spdlog $<$<BOOL:${MINGW}>:ws2_32>)
message(${CMAKE_BUILD_TYPE})

message(${LIBS})

set(src
        src/Game/Graphics/GE.cpp        src/Game/Graphics/GE.h
        src/Game/Nodes/GameObject.cpp   src/Game/Nodes/GameObject.h
        src/Game/GameConfiguration.cpp  src/Game/GameConfiguration.h
        src/Game/Nodes/NodeEmpty.cpp    src/Game/Nodes/NodeEmpty.h
        src/Game/Nodes/NodeSystem.cpp   src/Game/Nodes/NodeSystem.h
        src/Game/misc/GameMisc.cpp      src/Game/misc/GameMisc.h
        src/Game/Nodes/Node.cpp         src/Game/Nodes/Node.h
        src/properties/MessageBoard.h
        src/Game/graph/GX.cpp           src/Game/graph/GX.h
        src/main.cpp)

add_executable(${PROJECT_NAME} ${src})
target_link_libraries(${PROJECT_NAME} PRIVATE ${LIBS} )