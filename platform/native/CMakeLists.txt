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

add_library(${this} STATIC ${headers} ${sources})
target_link_libraries(${this} tymeshsys)

target_include_directories(${this} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}/sys")