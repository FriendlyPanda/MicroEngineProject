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

# Current SDL2 version: 2.26.2
set(SDL2_INCLUDE_DIR libs/SDL2/include/SDL2)
set(SDL2_LIB_DIR libs/SDL2/lib)

set(SDL2_IMAGE_INCLUDE_DIR libs/SDL2_image/include/SDL2)
set(SDL2_IMAGE_LIB_DIR libs/SDL2_image/lib)

set(GLFW_INCLUDE_DIR "C:/Program Files (x86)/GLFW/include")
set(GLFW_LIB_DIR "C:/Program Files (x86)/GLFW/lib")

set(VULKAN_INCLUDE_DIR C:/VulkanSDK/1.3.239.0/Include)
set(VULKAN_LIB_DIR C:/VulkanSDK/1.3.239.0/Lib)

set(GLM_INCLUDE_DIR C:/libraries/glm-0.9.9.8/glm)

include_directories(${SDL2_INCLUDE_DIR} ${SDL2_IMAGE_INCLUDE_DIR} ${GLFW_INCLUDE_DIR} ${GLM_INCLUDE_DIR} ${VULKAN_INCLUDE_DIR})

link_directories(${SDL2_LIB_DIR} ${SDL2_IMAGE_LIB_DIR} ${GLFW_LIB_DIR} ${VULKAN_LIB_DIR})

set(LIBS glfw3 vulkan-1 SDL2main SDL2 SDL2_image)
message(${CMAKE_BUILD_TYPE})

message(${LIBS})

set(main
        # src/main.cpp
        src/main_testbed.cpp)

set(src
        ${main}
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
        src/Game/Nodes/Node.h
        src/Game/Graphics_V2/GraphicalEngine.cpp
        src/Game/Graphics_V2/GraphicalEngine.h
        src/properties/MessageBoard.h)

add_executable(${PROJECT_NAME} ${src})

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/libs)
# target_link_libraries(${PROJECT_NAME} ${LIBS})
target_link_libraries(${PROJECT_NAME} PRIVATE spdlog::spdlog $<$<BOOL:${MINGW}>:ws2_32> ${LIBS})