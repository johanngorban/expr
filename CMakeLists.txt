cmake_minimum_required(VERSION 3.16)
project(expr)

set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE MATHEXPR_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
)

add_library(expr STATIC
    ${MATHEXPR_SOURCES}
)

target_include_directories(expr
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)
