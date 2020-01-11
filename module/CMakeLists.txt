cmake_minimum_required(VERSION 3.0.0)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99")

SET(this tymeshmodule)

if(BUILD_TEST)
    add_definitions(-DUTEST)
endif()

SET(headers
    utest_fixed.h
    utest_variable.h
    abc.h
)

SET(sources
    utest_fixed.c
    utest_variable.c
    abc.c
)

include_directories(.)
include_directories(../net)
include_directories(../dev)
add_library(${this} STATIC ${headers} ${sources})