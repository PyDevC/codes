cmake_minimum_required (VERSION 3.2)

project (Kalido)

set (CC "clang")
set (CXX "clang")
set (LLVM_FLAGS "llvm-config --cxxflags --ldflags --system-libs --libs=core")
set (CMAKE_BINARY_DIR "${PROJECT_SOURCE_DIR}/build/")
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib/static")
set (CMAKE_CXX_STANDARD 14)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0 `${LLVM_FLAGS}` -std=c++14")
set (source_dir "${PROJECT_SOURCE_DIR}/src/")
file (GLOB source_files "${source_dir}/*.cpp")

add_executable (Kalido ${source_files})
