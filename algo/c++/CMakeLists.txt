cmake_minimum_required (VERSION 3.2)

project (array)

set (CMAKE_BINARY_DIR "${PROJECT_SOURCE_DIR}/build/")
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib/static")
set (CMAKE_CXX_STANDARD 11)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -std=c++11")
set (source_dir "${PROJECT_SOURCE_DIR}/array/")
file (GLOB source_files "${source_dir}/*.cpp")

add_executable (Solid ${source_files})
