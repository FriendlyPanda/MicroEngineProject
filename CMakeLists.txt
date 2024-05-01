cmake_minimum_required(VERSION 3.24.1)
set(CMAKE_CXX_STANDARD 20)

#set(CMAKE_SKIP_BUILD_RPATH  FALSE)
#set(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE)
#list(APPEND CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/Assets/lib")
#set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

option(SHARED_LIB "build the project as a shared library" OFF)

project(
        "MEP"
        VERSION 1.0.0
        LANGUAGES CXX)

#add_subdirectory(lib/glfw)
#add_subdirectory(lib/glew)
add_subdirectory(lib/glm)
#add_subdirectory(lib/spdlog)

message(${CMAKE_SOURCE_DIR})

# GLFW

include_directories(lib/glfw/include)
link_directories(lib/glfw/lib)

add_library(glfw SHARED IMPORTED)
set_target_properties(glfw PROPERTIES
        IMPORTED_IMPLIB ${CMAKE_SOURCE_DIR}/lib/glfw/lib/libglfw3dll.a
        IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/lib/glfw/lib/libglfw3.a
        INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_SOURCE_DIR}/lib/glfw/include
)

# GLEW

include_directories(lib/glew/include)
link_directories(lib/glew/lib)

add_library(glew SHARED IMPORTED)
set_target_properties(glew PROPERTIES
        IMPORTED_IMPLIB ${CMAKE_SOURCE_DIR}/lib/glew/lib/libglew32.dll.a
        IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/lib/glew/lib/libglew32.a
        INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_SOURCE_DIR}/lib/glew/include
)

# ASSIMP

include_directories(lib/assimp/include)
link_directories(lib/assimp/lib)

add_library(assimp SHARED IMPORTED)
set_target_properties(assimp PROPERTIES
        IMPORTED_IMPLIB ${CMAKE_SOURCE_DIR}/lib/assimp/lib/libassimp.dll.a
        IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/lib/assimp/lib/libassimp.a
        INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_SOURCE_DIR}/lib/assimp/include
)

add_library(z STATIC IMPORTED)
set_target_properties(z PROPERTIES
        IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/lib/assimp/lib/libzlibstatic.a
)

include_directories(lib/spdlog/include)
link_directories(lib/spdlog/lib)


if(NOT TARGET spdlog)
    # Stand-alone build
#    find_package(spdlog REQUIRED)
    add_library(spdlog SHARED IMPORTED)
    set_target_properties(spdlog PROPERTIES
            IMPORTED_IMPLIB ${CMAKE_SOURCE_DIR}/lib/spdlog/lib/libspdlog.dll.a
            INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_SOURCE_DIR}/lib/spdlog/include
    )
endif()



#   Include the dll files in the build folder

set(DLL_FILES_LOC
        lib/assimp/bin/libassimp-5.dll
        lib/glew/bin/glew32.dll
        lib/glfw/bin/glfw3.dll
        lib/spdlog/bin/libspdlog.dll
)

foreach (file ${DLL_FILES_LOC})
    file(COPY ${file} DESTINATION ${CMAKE_BINARY_DIR})
endforeach ()

if(CMAKE_BUILD_TYPE MATCHES "Debug")
    message(debug_mode)
    file(COPY ${CMAKE_SOURCE_DIR}/Assets DESTINATION ${CMAKE_SOURCE_DIR}/cmake-build-debug)
    # unit testing
    add_subdirectory(Google_tests)

else ()
    message(release_mode)
    file(COPY ${CMAKE_SOURCE_DIR}/Assets DESTINATION ${CMAKE_SOURCE_DIR}/cmake-build-release)

endif ()


message(STATUS ${CMAKE_BUILD_TYPE})

#include_directories(lib/imgui)

set(IMGUI_PATH lib/imgui)
file(GLOB IMGUI_GLOB
        ${IMGUI_PATH}/imgui.h
        ${IMGUI_PATH}/imgui.cpp
        ${IMGUI_PATH}/imconfig.h
        ${IMGUI_PATH}/imgui_demo.cpp
        ${IMGUI_PATH}/imgui_draw.cpp
        ${IMGUI_PATH}/imgui_internal.h
        ${IMGUI_PATH}/imstb_rectpack.h
        ${IMGUI_PATH}/imstb_textedit.h
        ${IMGUI_PATH}/imstb_truetype.h
        ${IMGUI_PATH}/imgui_tables.cpp
        ${IMGUI_PATH}/imgui_widgets.cpp

        ${IMGUI_PATH}/backends/imgui_impl_glfw.h
        ${IMGUI_PATH}/backends/imgui_impl_glfw.cpp
        ${IMGUI_PATH}/backends/imgui_impl_opengl3.h
        ${IMGUI_PATH}/backends/imgui_impl_opengl3.cpp
        ${IMGUI_PATH}/backends/imgui_impl_opengl3_loader.cpp
)

add_library("imgui" STATIC ${IMGUI_GLOB})
target_include_directories("imgui" PUBLIC ${IMGUI_PATH})
target_link_libraries("imgui" PRIVATE glfw)

#set(imgui_src
#        lib/imgui/imconfig.h
#        lib/imgui/imgui.cpp
#        lib/imgui/imgui.h
#        lib/imgui/imgui_demo.cpp
#        lib/imgui/imgui_draw.cpp
#        lib/imgui/imgui_internal.h
#        lib/imgui/imgui_tables.cpp
#        lib/imgui/imgui_widgets.cpp
#        lib/imgui/imstb_rectpack.h
#        lib/imgui/imstb_textedit.h
#        lib/imgui/imstb_truetype.h
#        lib/imgui/misc/cpp/imgui_stdlib.cpp
#        lib/imgui/misc/cpp/imgui_stdlib.h
#        lib/imgui/backends/imgui_impl_opengl3.cpp
#        lib/imgui/backends/imgui_impl_opengl3.h
#        lib/imgui/backends/imgui_impl_glfw.cpp
#        lib/imgui/backends/imgui_impl_glfw.h
#)


set(src_headers
        src/Game/Graphics/GE.h
        src/Game/Graphics/components/Shaders/Shader.h
        src/Game/misc/InternalLogger.h
        src/Game/Graphics/components/VBO/VBO.h
        src/Game/Graphics/components/EBO/EBO.h
        src/Game/Graphics/components/VAO/VAO.h
        src/properties/MessageBoard.h
        src/Game/Graphics/UniformVarManager.h
        src/Game/NodeSystem/Nodes/BaseNode.h
        src/Game/NodeSystem/Nodes/Node_Model3D.h
        src/Game/Graphics/components/Model/MeshPrerequesite.h
        src/Game/Graphics/components/Model/Model.h
        src/Game/Graphics/components/Model/Mesh.h
        lib/stb/stb_image.h
        src/Game/Graphics/components/FBO/FBO.h
        src/Game/Graphics/components/camera/Camera.h
        src/Game/Graphics/components/RBO/RBO.h
        src/Game/Graphics/components/Texture/Texture.h
        src/Game/Graphics/modules/GUIBaseClass.h
        src/properties/MessageBoardConversion.h
        src/Game/NodeSystem/Nodes/Node_Object.h
        src/Game/NodeSystem/Nodes/Node_Mesh.h
)

#foreach (header_file ${src_headers})
#    file(COPY ${header_file} DESTINATION include/)
#endforeach ()

set(src
        src/Game/Graphics/GE.cpp
        src/Game/Graphics/components/Shaders/Shader.cpp
        src/Game/misc/InternalLogger.cpp
        src/Game/Graphics/components/VBO/VBO.cpp
        src/Game/Graphics/components/EBO/EBO.cpp
        src/Game/Graphics/components/VAO/VAO.cpp
        src/properties/MessageBoard.cpp
        src/Game/Graphics/UniformVarManager.cpp
        src/Game/NodeSystem/Nodes/Node_Model3D.cpp
        src/Game/Graphics/components/Model/Model.cpp
        src/Game/Graphics/components/Model/Mesh.cpp
        src/Game/Graphics/components/FBO/FBO.cpp
        src/Game/Graphics/components/camera/Camera.cpp
        src/Game/Graphics/components/RBO/RBO.cpp
        src/Game/Graphics/components/Texture/Texture.cpp
        src/generators/SplineGenerator3D.cpp
        src/Game/NodeSystem/Nodes/Node_Object.cpp
        src/Game/NodeSystem/Nodes/Node_Mesh.cpp
)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS TRUE)
find_package(OpenGL REQUIRED)
if(NOT OPENGL_FOUND)
    message(ERROR " OPENGL not found!")
endif(NOT OPENGL_FOUND)

if(${SHARED_LIB})
    add_library(${PROJECT_NAME} SHARED
            ${src}
            ${src_headers}
#            ${imgui_src}
    )
    target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_INSTALL_PREFIX}/include)
    target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_INSTALL_PREFIX}/bin/libMEP.dll)
    install(TARGETS ${PROJECT_NAME} LIBRARY DESTINATION lib)
    install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)
#    install(DIRECTORY include/ DESTINATION include)
    install(DIRECTORY ${CMAKE_SOURCE_DIR}/src/
            DESTINATION include/MEP
            FILES_MATCHING PATTERN "*.h" PATTERN "*.hpp")
else ()
    add_executable(${PROJECT_NAME} main.cpp ${src} ${src_headers}
#            ${imgui_src}
    )
endif ()

target_include_directories(${PROJECT_NAME} PRIVATE ${OPENGL_INCLUDE_DIR})

message(${CMAKE_SYSTEM_NAME})

if(CMAKE_SYSTEM_NAME MATCHES "Linux")
    # Code specific to Linux

    target_link_libraries(${PROJECT_NAME} PRIVATE
            glfw glew glm spdlog assimp assimp z
            # Add more static libraries as needed
    )

elseif(CMAKE_SYSTEM_NAME MATCHES "Windows")
    # Code specific to Windows
    message(STATUS ${LIBS})
    # set(CMAKE_EXE_LINKER_FLAGS "-static")
    target_link_libraries(${PROJECT_NAME} PRIVATE -static
            gcc
            glm
            z
    )

    target_link_libraries(${PROJECT_NAME} PRIVATE
            assimp
            glfw
            glew
            spdlog $<$<BOOL:${MINGW}>:ws2_32>
            ${OPENGL_gl_LIBRARY})

    target_link_libraries(${PROJECT_NAME} PUBLIC imgui)
    target_include_directories(${PROJECT_NAME} PUBLIC imgui)

else()
    message(FATAL_ERROR "Unsupported operating system: ${CMAKE_SYSTEM_NAME}")
endif()






