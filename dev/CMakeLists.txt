cmake_minimum_required(VERSION 3.0.0)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99")

SET(this tymeshdev)

if(BUILD_TEST)
    add_definitions(-DUTEST)
endif()

SET(headers
    tyheap.h
    tydebug.h
)

SET(sources
    tyheap.c 
    tydebug.c
)

include_directories(.)
add_library(${this} STATIC ${headers} ${sources})