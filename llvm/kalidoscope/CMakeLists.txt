cmake_minimum_required (VERSION 3.20)
project (Kalido)

# 1. Find LLVM and specify required components
# This replaces the manual 'llvm-config' calls by pulling in the correct metadata
find_package(LLVM REQUIRED CONFIG COMPONENTS 
    core 
    orcjit 
    native
)

include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})

# Output directories
set(CMAKE_BINARY_DIR "${PROJECT_SOURCE_DIR}/build")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib/static")

# 2. Use the modern C++ standard setting
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 3. Handle CXX flags 
# find_package(LLVM) automatically populates LLVM_DEFINITIONS and LLVM_INCLUDE_DIRS
# but for specific flags like -fno-rtti (often required by LLVM), we use:
separate_arguments(LLVM_CXX_FLAGS_LIST NATIVE_COMMAND "${LLVM_DEFINITIONS}")

# Sources
file(GLOB source_files "${PROJECT_SOURCE_DIR}/src/*.cpp")
add_executable(Kalido ${source_files})

# 4. Map components to library names
# This is equivalent to `llvm-config --libs core orcjit native`
llvm_map_components_to_libnames(llvm_libs core orcjit native)

# 5. Link everything
# This handles --ldflags and --system-libs automatically via the LLVM variables
target_link_libraries(Kalido PRIVATE 
    ${llvm_libs}
    ${LLVM_AVAILABLE_LIBS} # Optional: ensures all discovered LLVM libs are available
)

# Specifically add system dependencies (the --system-libs part)
target_link_libraries(Kalido PRIVATE "${LLVM_SYSTEM_LIBS}")
