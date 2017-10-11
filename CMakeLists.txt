cmake_minimum_required(VERSION 2.6)
project(rlrpg)

# Set the C++ standard used by the project
set(CMAKE_CXX_FLAGS "-std=c++17 -Wfatal-errors")

# Select all source files.
file(GLOB_RECURSE rlrpg_sources ./src/*.cpp)

# Add them to the library
add_library(rlrpg ${rlrpg_sources})

# Create an include directory
file(COPY "src/" DESTINATION "include/rlrpg/" FILES_MATCHING PATTERN "*.hpp" PATTERN "*.inl")
