cmake_minimum_required(VERSION 3.0.0)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")

SET(this tymeshsys)

if(BUILD_TEST)
    add_definitions(-DUTEST)
endif()

SET(headers
    env_variable.h
)

SET(sources
    env_variable.c
)

add_library(${this} STATIC ${headers} ${sources})
target_link_libraries(${this} tymeshprotocol protothread)

target_include_directories(${this} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")