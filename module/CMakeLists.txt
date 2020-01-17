cmake_minimum_required(VERSION 3.0.0)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")

SET(this tymeshmodule)

if(BUILD_TEST)
    add_definitions(-DUTEST)
endif()

SET(headers
    utest_fixed.h
    utest_variable.h
    abc.h
    neighbour.h
)

SET(sources
    utest_fixed.c
    utest_variable.c
    abc.c
    neighbour.c
)

add_library(${this} STATIC ${headers} ${sources})
target_link_libraries(${this} tymeshdev tymeshnet)

target_include_directories(${this} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")