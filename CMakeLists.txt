cmake_minimum_required(VERSION 3.15)
project(MathCyb2020)

set(CMAKE_CXX_STANDARD 14)
set(Boost_INCLUDE_DIR "C:/boost/include/boost-1_74")
set(Boost_LIBRARY_DIR "C:/boost/lib")
set(BOOST_ROOT "C:/boost")

find_package(Boost REQUIRED)
if(Boost_FOUND)
    message(STATUS "Boost_INCLUDE_DIRS: ${Boost_INCLUDE_DIRS}")
    message(STATUS "Boost_LIBRARIES: ${Boost_LIBRARIES}")
    message(STATUS "Boost_VERSION: ${Boost_VERSION}")
    include_directories(${Boost_INCLUDE_DIRS})
endif()

include_directories(.)

add_executable(MathCyb2020
        .idea/.gitignore
        .idea/MathCyb2020.iml
        .idea/misc.xml
        .idea/modules.xml
        .idea/vcs.xml
        .idea/workspace.xml
        main.cpp
        block.h block.cpp blockchain.cpp blockchain.h)
if(Boost_FOUND)
    # Note: a target should be already defined using 'add_executable' or 'add_library'
    target_link_libraries(MathCyb2020 ${Boost_LIBRARIES})
endif()


