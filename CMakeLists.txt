cmake_minimum_required(VERSION 3.5) # Definitions 

set(PROJECT_NAME tymesh) 

if(BUILD_TEST)
    set(BUILD_TOOL ON)
    set(CMAKE_BUILD_TYPE Debug)
endif()

add_subdirectory(lib)
add_subdirectory(dev) 
add_subdirectory(net) 

if(BUILD_TEST)
    add_subdirectory(test)
endif()

if(BUILD_TOOL)
endif()