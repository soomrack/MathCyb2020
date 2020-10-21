cmake_minimum_required (VERSION 3.17)
project (lib)

set(SOURCE_LIB
        src/block.cpp
        src/blockchain.cpp
        )

add_library(lib STATIC ${SOURCE_LIB})