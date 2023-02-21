cmake_minimum_required(VERSION 3.24)
set(CMAKE_CXX_STANDARD 20)

set(project_name MEP)
project(${project_name})

# Current SDL2 version: 2.26.2
set(SDL2_INCLUDE_DIR SDL2/include/SDL2)
set(SDL2_LIB_DIR SDL2/lib)

set(SDL2_IMAGE_INCLUDE_DIR SDL2_image/include/SDL2)
set(SDL2_IMAGE_LIB_DIR SDL2_image/lib)

include_directories(${SDL2_INCLUDE_DIR} ${SDL2_IMAGE_INCLUDE_DIR})

link_directories(${SDL2_LIB_DIR} ${SDL2_IMAGE_LIB_DIR})

set(LIBS SDL2main SDL2 SDL2_image)
message(${CMAKE_BUILD_TYPE})

message(${LIBS})

set(src
        src/main.cpp
        src/Game/Graphics/GE.cpp
        src/Game/Graphics/GE.h
        src/Game/Graphics/GE_init.cpp
        src/Game/Graphics/GE_close.cpp
        src/Game/Graphics/GE_rend.cpp
        src/Game/Nodes/GameObject.cpp
        src/Game/Nodes/GameObject.h
        src/Game/Nodes/NodeSprite.cpp
        src/Game/Nodes/NodeSprite.h
        src/Game/GameConfiguration.cpp
        src/Game/GameConfiguration.h
        src/Game/Nodes/NodeEmpty.cpp
        src/Game/Nodes/NodeEmpty.h
        src/Game/Graphics/TextureManager.h
        src/Game/Nodes/NodeSystem.cpp
        src/Game/Nodes/NodeSystem.h
        src/Game/misc/Box.h
        src/Game/misc/Quadtree.h
        src/Game/misc/Vector2.h
        src/Game/misc/GameMisc.cpp
        src/Game/misc/GameMisc.h
        src/Game/Nodes/Node.cpp
        src/Game/Nodes/Node.h)

add_executable(${project_name} ${src})


target_link_libraries(${project_name} ${LIBS})