cmake_minimum_required(VERSION 3.24)
project(clrs_neon LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# ----------------------------------------------------------------------------------------------
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()
include(GoogleTest)

# ----------------------------------------------------------------------------------------------
function(clrs_add_test name)
    add_executable(${name} tests/${name}.cxx)
    target_link_libraries(${name} PRIVATE GTest::gtest_main)
    target_include_directories(${name} PRIVATE include)
    target_compile_options(${name} PRIVATE -Wall -Wextra -Wpedantic -Wconversion)
    gtest_discover_tests(${name})
endfunction()

clrs_add_test(sum_test)
