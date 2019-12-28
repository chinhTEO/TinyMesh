cmake_minimum_required(VERSION 3.5) # Definitions 

set(PROJECT_NAME tymesh) 

set(BUILD_TEST ON)

add_subdirectory(lib)
add_subdirectory(dev) 

if(BUILD_TEST)
    add_subdirectory(test)
endif()