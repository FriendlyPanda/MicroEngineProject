cmake_minimum_required(VERSION 3.22.1)
set(CMAKE_CXX_STANDARD 20)

#set(CMAKE_SKIP_BUILD_RPATH  FALSE)
#set(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE)
#list(APPEND CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/Assets/lib")
#set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

option(SHARED_LIB "build the project as a shared library" OFF)
option(BUILD_SAMPLE_PLUGIN "Build Sample Plugin" ON)

project(
        "MEP"
        VERSION 1.0.0
        LANGUAGES CXX)

add_subdirectory(lib/glm)
message(STATUS ${CMAKE_SYSTEM_NAME})
message(${CMAKE_SOURCE_DIR})

if(CMAKE_SYSTEM_NAME MATCHES "Linux")
    # Code specific to Linux


    find_package(GLEW REQUIRED)
    find_package(glfw3 REQUIRED)
    find_package(glm REQUIRED)
    find_package(spdlog REQUIRED)
    find_library(DL_LIBRARY dl)


elseif(CMAKE_SYSTEM_NAME MATCHES "Windows")
    # Code specific to Windows

    # NOTE:
    # if the libraries were installed without changing from the default installation directory, everything should work as is
    # otherwise please remember to change the directories

    # GLFW : developed on -> 3.4
    set(GLFW_DIR "C:/Program Files (x86)/GLFW/")
    set(glfw3_DIR "${GLFW_DIR}lib/cmake/glfw3")
    set(glfw3_INCLUDE_DIRS "${GLFW_DIR}include")
    set(glfw3_bin "${GLFW_DIR}bin/glfw3.dll")

    find_package(glfw3 REQUIRED)
    if(glfw3_FOUND)
        message(STATUS "GLFW3 was found.")
        get_target_property(GLFW3_LOCATION glfw LOCATION)
        message(STATUS "GLFW3 location: ${GLFW3_LOCATION}")
    else()
        message(STATUS "GLFW3 wasn't found.")
    endif()


    # GLEW : developed on -> 2.1.0
    find_package(GLEW REQUIRED)

    if(GLEW_FOUND)
        message(STATUS "GLEW was found.")
        get_target_property(GLEW_LOCATION GLEW::glew LOCATION)
        message(STATUS "GLEW location: ${GLEW_LOCATION}")
    else()
        message(STATUS "GLEW wasn't found.")
    endif()


    # spdlog : developed on -> 1.14.1
    if(NOT TARGET spdlog)
        # Stand-alone build
        find_package(spdlog REQUIRED)
        if(spdlog_FOUND)
            message(STATUS "spdlog was found.")
            get_target_property(spdlog_LOCATION spdlog::spdlog LOCATION)
            message(STATUS "spdlog location: ${spdlog_LOCATION}")
        else()
            message(STATUS "spdlog wasn't found.")
        endif()
    endif()



    #   Include the dll files in the build folder

    set(DLL_FILES_LOC
#            lib/assimp/bin/libassimp-5.dll
            ${GLFW3_LOCATION}
            ${GLEW_LOCATION}
            ${spdlog_LOCATION}
    )

    foreach (file ${DLL_FILES_LOC})
        file(COPY ${file} DESTINATION ${CMAKE_BINARY_DIR})
    endforeach ()

    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS TRUE)

endif ()



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


set(src_headers
        src/Engine/Graphics/GE.h
        src/Engine/Graphics/components/Shaders/Shader.h
        src/Engine/misc/InternalLogger.h
        src/Engine/Graphics/components/VBO/VBO.h
        src/Engine/Graphics/components/EBO/EBO.h
        src/Engine/Graphics/components/VAO/VAO.h
        src/properties/MessageBoard.h
        src/Engine/Graphics/UniformVarManager.h
        src/Engine/NodeSystem/Nodes/BaseNode.h
        src/Engine/NodeSystem/Nodes/Node_Model3D.h
        src/Engine/Graphics/components/Model/MeshPrerequesite.h
        src/Engine/Graphics/components/Model/Model.h
        src/Engine/Graphics/components/Model/Mesh.h
        lib/stb/stb_image.h
        src/Engine/Graphics/components/FBO/FBO.h
        src/Engine/Graphics/components/camera/Camera.h
        src/Engine/Graphics/components/RBO/RBO.h
        src/Engine/Graphics/components/Texture/Texture.h
        src/Engine/Graphics/modules/GUIBaseClass.h
        src/properties/MessageBoardConversion.h
        src/Engine/NodeSystem/Nodes/Node_Object.h
        src/Engine/NodeSystem/Nodes/Node_Mesh.h
)

set(src
        src/Engine/Graphics/GE.cpp
        src/Engine/Graphics/components/Shaders/Shader.cpp
        src/Engine/misc/InternalLogger.cpp
        src/Engine/Graphics/components/VBO/VBO.cpp
        src/Engine/Graphics/components/EBO/EBO.cpp
        src/Engine/Graphics/components/VAO/VAO.cpp
        src/properties/MessageBoard.cpp
        src/Engine/Graphics/UniformVarManager.cpp
        src/Engine/NodeSystem/Nodes/Node_Model3D.cpp
        src/Engine/Graphics/components/Model/Model.cpp
        src/Engine/Graphics/components/Model/Mesh.cpp
        src/Engine/Graphics/components/FBO/FBO.cpp
        src/Engine/Graphics/components/camera/Camera.cpp
        src/Engine/Graphics/components/RBO/RBO.cpp
        src/Engine/Graphics/components/Texture/Texture.cpp
        src/generators/SplineGenerator3D.cpp
        src/Engine/NodeSystem/Nodes/Node_Object.cpp
        src/Engine/NodeSystem/Nodes/Node_Mesh.cpp
        src/PluginManager/PluginInterface.h
        src/PluginManager/PluginManager.cpp
        src/PluginManager/PluginManager.h
)

if(${BUILD_SAMPLE_PLUGIN})
    message("Building sample library")
    add_subdirectory(src/PluginManager/SamplePlugin)
endif ()

find_package(OpenGL REQUIRED)
if(NOT OPENGL_FOUND)
    message(ERROR " OPENGL not found!")
endif(NOT OPENGL_FOUND)

if(${SHARED_LIB})
    add_library(${PROJECT_NAME} SHARED
            ${src}
            ${src_headers}
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
            GL glfw GLEW glm spdlog::spdlog ${DL_LIBRARY}
            # Add more static libraries as needed
    )

    target_link_libraries(${PROJECT_NAME} PUBLIC imgui)
    target_include_directories(${PROJECT_NAME} PUBLIC imgui)

elseif(CMAKE_SYSTEM_NAME MATCHES "Windows")
    # Code specific to Windows
    message(STATUS ${LIBS})
    # set(CMAKE_EXE_LINKER_FLAGS "-static")
    target_link_libraries(${PROJECT_NAME} PRIVATE -static
#            gcc
            glm
#            z
    )

    target_link_libraries(${PROJECT_NAME} PRIVATE
#            assimp
            glfw
            GLEW::glew
            spdlog::spdlog $<$<BOOL:${MINGW}>:ws2_32>
            ${OPENGL_gl_LIBRARY}
    )

    target_link_libraries(${PROJECT_NAME} PUBLIC imgui)
    target_include_directories(${PROJECT_NAME} PUBLIC imgui)
else()
    message(FATAL_ERROR "Unsupported operating system: ${CMAKE_SYSTEM_NAME}")
endif()






