cmake_minimum_required(VERSION 3.0.0)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")

SET(this tymeshdev)

if(BUILD_TEST)
    add_definitions(-DUTEST)
endif()

SET(headers
    tyheap.h
    tydebug.h
    queue.h
)

SET(sources
    tyheap.c 
    tydebug.c
    queue.c
)

add_library(${this} STATIC ${headers} ${sources})

target_include_directories(${this} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")