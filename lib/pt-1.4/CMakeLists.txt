cmake_minimum_required(VERSION 3.1.0)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")

SET(this protothread)

add_library(${this} INTERFACE)
target_include_directories(${this} INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}")

