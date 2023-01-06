cmake_minimum_required(VERSION 3.24)
set(CMAKE_CXX_STANDARD 20)

set(project_name MEP)
project(${project_name})


# Current SDL2 version: 2.26.2
set(SDL2_INCLUDE_DIR SDL2/include/SDL2)
set(SDL2_LIB_DIR SDL2/lib)

include_directories(${SDL2_INCLUDE_DIR})
link_directories(${SDL2_LIB_DIR})

set(src
        src/main.cpp
        src/Graphics/GraphicEngine.cpp
        src/Graphics/GraphicEngine.h
        )

add_executable(${project_name} ${src})

set(LIBS SDL2main SDL2)
target_link_libraries(${project_name} ${LIBS})