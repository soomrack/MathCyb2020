cmake_minimum_required(VERSION 3.15)
project(MathCyb2020)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(MathCyb2020
        .idea/.gitignore
        .idea/MathCyb2020.iml
        .idea/misc.xml
        .idea/modules.xml
        .idea/vcs.xml
        .idea/workspace.xml
        main.cpp
        readme.txt block.h block.cpp blockchain.cpp blockchain.h)