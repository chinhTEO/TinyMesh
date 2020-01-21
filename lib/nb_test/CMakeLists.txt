cmake_minimum_required(VERSION 3.0.0)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")

SET(this nb_test)

SET(BUILD_TEST ON)

if(BUILD_TEST)
    add_definitions(-DBUILD_TEST=1)
    add_definitions(-DNBT_UTEST_SUPPORT=1)
endif()

SET(headers
    inc/nb_test.h
    src/queue.h
)

SET(sources
    src/nb_test.c
    src/queue.c
)

add_library(${this} STATIC ${headers} ${sources})
target_include_directories(${this} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/inc")

add_subdirectory(test) 