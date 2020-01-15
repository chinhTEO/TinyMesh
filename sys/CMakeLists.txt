cmake_minimum_required(VERSION 3.0.0)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99")

SET(this tymeshsys)

if(BUILD_TEST)
    add_definitions(-DUTEST)
endif()

SET(headers
    cc-gcc.h
    cc.h
    lc-addrlabels.h
    lc-switch.h
    lc.h
    process.h
    pt-sem.h
    pt.h
)

SET(sources
    process.c
)

include_directories(.)

add_library(${this} STATIC ${headers} ${sources})