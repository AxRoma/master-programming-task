cmake_minimum_required(VERSION 3.20)
project(iomanip_lab CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Подтягиваем Catch2 прямо из Git (без Homebrew/Boost)
include(FetchContent)
FetchContent_Declare(
  catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG v3.6.0
)
FetchContent_MakeAvailable(catch2)

# Заголовочная библиотека с нашими манипуляторами
add_library(iomanip INTERFACE)
target_include_directories(iomanip INTERFACE include)

# Защитный TU, чтобы хедер точно участвовал в сборке
file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/gprotect.cpp "#include <iomanip.hpp>\n")

# Тесты
file(GLOB TESTS tests/*.cpp)
add_executable(tests_iomanip ${TESTS} ${CMAKE_CURRENT_BINARY_DIR}/gprotect.cpp)
target_link_libraries(tests_iomanip PRIVATE iomanip Catch2::Catch2WithMain)

# Интеграция с CTest/Catch2
include(CTest)
include(Catch)
catch_discover_tests(tests_iomanip)
