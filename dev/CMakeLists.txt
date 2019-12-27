cmake_minimum_required(VERSION 3.0.0)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99")

cmake_minimum_required(VERSION 3.0.0)

SET(this tymeshdev)

SET(headers
    tyheap.h
)

SET(sources
    tyheap.c 
)

include_directories(.)
add_library(${this} STATIC ${headers} ${sources})