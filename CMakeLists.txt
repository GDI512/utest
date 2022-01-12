cmake_minimum_required (VERSION 3.15)

project (utest VERSION 1.0.0 LANGUAGES CXX)

enable_testing ()

if ("${CMAKE_SOURCE_DIR}" STREQUAL "${PROJECT_SOURCE_DIR}")
    add_subdirectory (src)
    add_subdirectory (test)
else ()
    add_subdirectory (src)
endif ()
