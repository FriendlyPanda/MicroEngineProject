cmake_minimum_required(VERSION 3.24.1)
set(CMAKE_CXX_STANDARD 20)

project(
        "MEP"
        VERSION 1.0.0
        LANGUAGES CXX)

add_subdirectory(libs/glfw)
add_subdirectory(libs/glew)
add_subdirectory(libs/glm)
add_subdirectory(libs/spdlog)

add_library(assimp STATIC IMPORTED)
set_target_properties(assimp PROPERTIES
        IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/libs/Assimp/lib/libassimp.a
        INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_SOURCE_DIR}/libs/Assimp/include
)

add_library(z STATIC IMPORTED)
set_target_properties(z PROPERTIES
        IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/libs/Assimp/lib/libzlibstatic.a
)

if(CMAKE_BUILD_TYPE MATCHES "Debug")
    message(debug_mode)
    # unit testing
    add_subdirectory(Google_tests)
else ()
    message(release_mode)
endif ()


message(STATUS ${CMAKE_BUILD_TYPE})

set(src
        src/Game/Graphics/GE.cpp
        src/Game/Graphics/GE.h
        src/Game/Graphics/Shaders/Shader.cpp
        src/Game/Graphics/Shaders/Shader.h
        src/Game/InternalLogger.cpp
        src/Game/InternalLogger.h
        src/Game/Graphics/VBO/VBO.cpp
        src/Game/Graphics/VBO/VBO.h
        src/Game/Graphics/EBO/EBO.cpp
        src/Game/Graphics/EBO/EBO.h
        src/Game/Graphics/VAO/VAO.cpp
        src/Game/Graphics/VAO/VAO.h
        src/properties/MessageBoard.cpp
        src/properties/MessageBoard.h
        src/main.cpp
        src/Game/Graphics/UniformVarManager.cpp
        src/Game/Graphics/UniformVarManager.h
        src/Game/NodeSystem/Nodes/BaseNode.h
        src/Game/NodeSystem/Nodes/Node_Model3D.cpp
        src/Game/NodeSystem/Nodes/Node_Model3D.h
        src/Game/Graphics/Model/MeshPrerequesite.h
        src/Game/Graphics/Model/Model.cpp
        src/Game/Graphics/Model/Model.h
        src/Game/Graphics/Model/Mesh.cpp
        src/Game/Graphics/Model/Mesh.h
)


add_executable(${PROJECT_NAME} ${src})



message(${CMAKE_SYSTEM_NAME})

if(CMAKE_SYSTEM_NAME MATCHES "Linux")
    # Code specific to Linux
    find_package(OpenGL REQUIRED)
    target_link_libraries(${PROJECT_NAME} PRIVATE
            libglew_static glfw glm spdlog::spdlog assimp
            # Add more static libraries as needed
    )

elseif(CMAKE_SYSTEM_NAME MATCHES "Windows")
    # Code specific to Windows
    message(STATUS ${LIBS})
    # set(CMAKE_EXE_LINKER_FLAGS "-static")
    target_link_libraries(${PROJECT_NAME} PRIVATE -static glfw libglew_static glm spdlog::spdlog assimp z)


else()
    message(FATAL_ERROR "Unsupported operating system: ${CMAKE_SYSTEM_NAME}")
endif()






