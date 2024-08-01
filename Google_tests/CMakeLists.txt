project(Google_tests)
add_subdirectory(lib)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

set(src
        MessageBoardTest.cpp
        SafeConversionTest.cpp
        ../default_libs/MessageBoard/MesageBoard/MessageBoard.cpp
        ../default_libs/MessageBoard/MesageBoard/MessageBoard.h
        ../default_libs/MessageBoard/MesageBoard/MessageBoardConversion.h

)

add_executable(Google_Tests_run ${src})

target_link_libraries(Google_Tests_run gtest gtest_main)