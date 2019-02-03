cmake_minimum_required(VERSION 3.10)
project(RayTracing)

set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE SOURCE_FILES src/*.cpp)

file(GLOB_RECURSE HEADER_FILES src/*.h)

add_executable(RayTracing ${SOURCE_FILES})