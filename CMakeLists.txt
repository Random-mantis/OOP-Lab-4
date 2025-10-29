cmake_minimum_required(VERSION 3.16)
project(FiguresProject LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_library(figures_lib INTERFACE)
target_include_directories(figures_lib INTERFACE ${CMAKE_SOURCE_DIR}/Libs)

add_executable(prog1 program.cpp)
target_link_libraries(prog1 PRIVATE figures_lib)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)
set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()
add_executable(testing tests/test.cpp)
target_link_libraries(testing PRIVATE figures_lib GTest::gtest_main)
include(GoogleTest)
gtest_discover_tests(testing)