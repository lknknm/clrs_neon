cmake_minimum_required(VERSION 3.24)
project(clrs_neon LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
  sum_test 
  tests/sum_test.cxx 
)
target_link_libraries(
  sum_test
  GTest::gtest_main
)

target_compile_options(sum_test PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Werror)
target_include_directories(sum_test
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

include(GoogleTest)
gtest_discover_tests(sum_test)
