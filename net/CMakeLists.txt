cmake_minimum_required(VERSION 3.0.0)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99")

SET(this tymeshnet)

add_subdirectory(module)

if(BUILD_TEST)
    add_definitions(-DUTEST)
endif()

SET(headers
    message.h
    message_variable.h
    message_fixed.h
    message_define.h
)

SET(sources
    message_variable.c
    message_fixed.c
    message_define.c
    message.c
)

include_directories(.)
include_directories(./module)
include_directories("${CMAKE_SOURCE_DIR}/dev")

add_library(${this} STATIC ${headers} ${sources})
target_link_libraries(${this} tymeshdev tymeshmodule)