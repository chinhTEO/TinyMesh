cmake_minimum_required(VERSION 3.0.0)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")

SET(this tymeshnet)

if(BUILD_TEST)
    add_definitions(-DUTEST)
endif()

SET(headers
    message.h
    message_variable.h
    message_fixed.h
    message_define.h
    tymesh_framer.h
)

SET(sources
    message_variable.c
    message_fixed.c
    message_define.c
    message.c
    tymesh_framer.c
)

add_library(${this} STATIC ${headers} ${sources})
target_link_libraries(${this} tymeshdev tymeshmodule)

target_include_directories(${this} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")