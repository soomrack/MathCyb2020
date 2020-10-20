cmake_minimum_required(VERSION 3.17)
project(MathCyb2020)

set(CMAKE_CXX_STANDARD 14)

find_package(Boost 1.73.0)

if(Boost_FOUND)
    message(STATUS "Boost_INCLUDE_DIRS: ${Boost_INCLUDE_DIRS}")
    message(STATUS "Boost_LIBRARIES: ${Boost_LIBRARIES}")
    message(STATUS "Boost_VERSION: ${Boost_VERSION}")
    include_directories(${Boost_INCLUDE_DIRS})
endif()

include_directories(lib)
add_subdirectory(lib)

set(SOURCE_EXE main.cpp)
add_executable(main ${SOURCE_EXE})

target_link_libraries(main lib)

if(Boost_FOUND)
    target_link_libraries(main ${Boost_LIBRARIES})
endif()
