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
)

add_executable(${PROJECT_NAME} ${src})

message(${CMAKE_SYSTEM_NAME})

if(CMAKE_SYSTEM_NAME MATCHES "Linux")
    # Code specific to Linux
    find_package(OpenGL REQUIRED)
    target_link_libraries(${PROJECT_NAME} PRIVATE
            libglew_static glfw glm spdlog::spdlog
            # Add more static libraries as needed
    )

elseif(CMAKE_SYSTEM_NAME MATCHES "Windows")
    # Code specific to Windows
    set(LIBS glfw libglew_static glm spdlog::spdlog)
    message(STATUS ${LIBS})
    # set(CMAKE_EXE_LINKER_FLAGS "-static")
    target_link_libraries(${PROJECT_NAME} PRIVATE -static ${LIBS} )


else()
    message(FATAL_ERROR "Unsupported operating system: ${CMAKE_SYSTEM_NAME}")
endif()






