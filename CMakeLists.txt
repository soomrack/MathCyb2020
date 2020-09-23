cmake_minimum_required(VERSION 3.17)
project(MathCyb2020)

set(CMAKE_CXX_STANDARD 14)
set(SOURCE_EXE main.cpp)

include_directories(lib)
add_executable(main ${SOURCE_EXE})
add_subdirectory(lib)
target_link_libraries(main lib)