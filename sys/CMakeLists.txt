cmake_minimum_required(VERSION 3.0.0)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")

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
    clock.h
    rtimer.h
)

SET(sources
    process.c
    rtimer.c
)

add_library(${this} STATIC ${headers} ${sources})
target_link_libraries(${this} tymeshplatform)

target_include_directories(${this} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")