cmake_minimum_required(VERSION 2.8)
project(Decorator)

# ==========================================================================
# Include things

# Provides define_file_basename_for_sources
include(basename.cmake)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR})

# ==========================================================================
# Ensure directories exist
# ==========================================================================

file(MAKE_DIRECTORY bin)
file(MAKE_DIRECTORY lib)
file(MAKE_DIRECTORY modules)
file(MAKE_DIRECTORY logs)
file(MAKE_DIRECTORY includes)
file(MAKE_DIRECTORY src)
file(MAKE_DIRECTORY doc)
file(MAKE_DIRECTORY design)

# ==========================================================================
# Setup other things
# ==========================================================================

# ==========================================================================
# Setup env
# ==========================================================================

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# ==========================================================================
# Set requirements and flags
# ==========================================================================

# CMAKE_CXX_STANDARD is not present below cmake 3.1
set(CMAKE_CXX_FLAGS "-Wall -Wextra -pedantic -Werror -std=c++11")
set(CMAKE_CC_FLAGS "-Wall -Wextra -pedantic -Werror -std=c++11")

# ==========================================================================
# Include headers
# ==========================================================================

include_directories(include)

# ==========================================================================
# Link from lib/
# ==========================================================================

link_directories(${CMAKE_BINARY_DIR}/lib/)

# ==========================================================================
# Include from modules and set up
# ==========================================================================

include_directories(modules/)

# ==========================================================================
# Find libraries
# ==========================================================================

# ==========================================================================
#  Define targets
# ==========================================================================
# set_target_properties(target PROPERTIES ...)
# target_compile_features(target features...)
# !!! target_compile_features is not available below cmake 3.1

# add_executable()
# add_library()

add_executable(atomic src/example_atomic.cpp)
target_link_libraries(atomic PRIVATE pthread)

add_executable(memoize src/example_memoize.cpp)
target_link_libraries(memoize PRIVATE pthread)

add_executable(log src/example_log.cpp)
target_link_libraries(log PRIVATE pthread)

