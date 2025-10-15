cmake_minimum_required(VERSION 3.15)
project(iomanip_lab LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG v3.4.0
)
FetchContent_MakeAvailable(Catch2)

add_library(iomanip INTERFACE)
target_include_directories(iomanip INTERFACE include)

file(GLOB TESTS tests/*.cpp)
add_executable(tests_iomanip ${TESTS})
target_link_libraries(tests_iomanip iomanip Catch2::Catch2WithMain)

include(CTest)
include(Catch)
catch_discover_tests(tests_iomanip)
