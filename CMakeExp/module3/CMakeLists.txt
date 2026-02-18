cmake_minimum_required(VERSION 3.15...4.1)

project(Variables)

set(MY_VAR "var")
set(NEW_VAR "new-${MY_VAR}")
message(${MY_VAR})
message(${NEW_VAR})
set(SIMPLE "VALUE" CACHE STRING "disk")
message(${SIMPLE})

mark_as_advanced(SIMPLE)

option(ENABLE_CUDA "Compile the code with CUDA" OFF) # You can easily turn it on

# IMP: You should not use Environment variables in CMake cause your cmake file moves from machine to machine and each machine has different variables making it hard to reproduce bugs and same general configurations, you configuration is prone to errors
# Also it leads to poor integration with IDEs

set(ENV{SIMPL} "value")
