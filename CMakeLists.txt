cmake_minimum_required(VERSION 3.5) # Definitions 

set(PROJECT_NAME tymesh) 

set(BUILD_TEST ON)
set(BUILD_TOOL ON)

add_subdirectory(lib)
add_subdirectory(dev) 
add_subdirectory(net) 

if(BUILD_TEST)
    add_subdirectory(test)
endif()

if(BUILD_TOOL)
endif()