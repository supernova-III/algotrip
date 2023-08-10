cmake_minimum_required(VERSION 3.25)

project(algotrip LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.14.0)
set(BUILD_GMOCK OFF)
set(INSTALL_GTEST OFF)
FetchContent_MakeAvailable(googletest)

add_executable(${PROJECT_NAME} src/main.cpp)
target_precompile_headers(${PROJECT_NAME} PRIVATE
  <string>
  <algorithm>
  <numeric>
  <vector>
)

set_target_properties(${PROJECT_NAME} PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

target_link_libraries(${PROJECT_NAME} GTest::gtest GTest::gtest_main)
