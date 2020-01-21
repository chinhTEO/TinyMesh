cmake_minimum_required(VERSION 3.5) # Definitions 

set(PROJECT_NAME tymesh) 

set(PLATFORM_NATIVE ON)

if(PLATFORM_NATIVE)
    add_definitions(-D_POSIX_C_SOURCE=200809L)
endif()

if(BUILD_TEST)
    set(BUILD_TOOL ON)
    add_definitions(-DDEBUG=1)
    add_definitions(-DNBT_UTEST_SUPPORT=1)
    set(CMAKE_BUILD_TYPE Debug)
endif()

add_subdirectory(lib)
add_subdirectory(dev) 
add_subdirectory(net) 
add_subdirectory(module)
add_subdirectory(sys)
add_subdirectory(platform)
add_subdirectory(protocol)

if(BUILD_TEST)
    add_subdirectory(test)
endif()

if(BUILD_TOOL)
endif()