project(Google_tests)
add_subdirectory(lib)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

set(src
        MessageBoardTest.cpp
        ../src/properties/MessageBoard.cpp
        ../src/properties/MessageBoard.h
)

add_executable(Google_Tests_run ${src})

target_link_libraries(Google_Tests_run gtest gtest_main)