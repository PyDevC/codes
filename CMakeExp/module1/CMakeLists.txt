cmake_minimum_required(VERSION 3.20...4.1)

project(Exp VERSION 1.0 DESCRIPTION "Modern way of writing CMake" LANGUAGES CXX)

add_executable(one two.cpp three.h)
add_library(two STATIC two.cpp three.h)
target_include_directories(one PUBLIC include)
add_library(another STATIC another.cpp another.h)
target_link_directories(another PUBLIC one)
