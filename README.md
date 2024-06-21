# MicroEngineProject
Graphics engine project.

## features:
- Shader loader with integrated Uniform variable scan
- Message system for multiple languages
- windows compatibility (linux work in progress)
- inbuilt logger
- GoogleTests (Debug only)

## Installation
### Clion instructions
This is done using mingw32-w64

1. pull the latest version of the repo
2. pull all the required submodules
```commandline
git submodule init
git submodule update
```
3. open cmake and select build type, shared library and installation location. configure and generate
4. build using mingw
```commandline
mingw32-make
mingw32-make install
```
5. put the bin, include and lib into your project
6. add these lines to the CMakeLists.txt (the paths may vary depending on the project)
```cmake
# adding the library
include_directories(libs/MEP/include)
link_directories(libs/MEP/lib)

add_library(MEP SHARED IMPORTED)
set_target_properties(MEP PROPERTIES
        IMPORTED_IMPLIB ${CMAKE_SOURCE_DIR}/libs/MEP/lib/libMEP.dll.a
        INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_SOURCE_DIR}/libs/MEP/include
)

# adding the .dll and the Assets to the output folder
file(COPY libs/MEP/bin/libMEP.dll DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${CMAKE_SOURCE_DIR}/Assets DESTINATION ${CMAKE_SOURCE_DIR}/output)

# ...
# linking the library

target_link_libraries(${PROJECT_NAME} PRIVATE MEP)

target_include_directories(${PROJECT_NAME} PUBLIC libs/MEP/include)
```
> **NOTE:** The project relies on: glfw, glew, glm, imgui, spdlog and stb. Implementation may vary.

6. Include the Asset folder in the root folder of the project, the layout should be as follows:
```
.
└── Assets/
    ├── properties/
    │   └── config.properties
    └── Shaders
```
> **Note:** an example Asset folder can be found in the repository
4. build the project
6. run the project 