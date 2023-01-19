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

set(src
        src/main.cpp
        src/Graphics/GE.cpp
        src/Graphics/GE.h
        src/Graphics/GE_init.cpp
        src/Graphics/GE_close.cpp
        src/Graphics/GE_rend.cpp
        src/Game/GameObject.cpp
        src/Game/GameObject.h
        src/Game/GameSprite.cpp
        src/Game/GameSprite.h
        src/Game/GameConfiguration.cpp
        src/Game/GameConfiguration.h)

add_executable(${project_name} ${src})

set(LIBS SDL2main SDL2 SDL2_image)
target_link_libraries(${project_name} ${LIBS})