cmake_minimum_required(VERSION 3.30)
project(quadratic_bezier_splines C)

set(CMAKE_C_STANDARD 11)

include(FetchContent)

FetchContent_Declare(
        hard_assert
        GIT_REPOSITORY https://github.com/CesarBerriot/hard_assert.git
        GIT_TAG master
)
FetchContent_MakeAvailable(hard_assert)

add_library(quadratic_bezier_splines STATIC quadratic_bezier_splines.c)
target_include_directories(quadratic_bezier_splines PUBLIC include)
target_compile_options(quadratic_bezier_splines PRIVATE -ansi -pedantic-errors -std=c11 -Wall -Wextra)
target_link_libraries(quadratic_bezier_splines PRIVATE hard_assert)