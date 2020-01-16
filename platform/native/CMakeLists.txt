cmake_minimum_required(VERSION 3.0.0)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")

SET(this tymeshplatform)

if(BUILD_TEST)
    add_definitions(-DUTEST)
endif()

SET(headers
    sys/rtimer-arch.h
)

SET(sources
    sys/clock.c
    sys/rtimer-arch.c
)

include_directories(.)
include_directories(${CMAKE_SOURCE_DIR}/sys)

add_library(${this} STATIC ${headers} ${sources})