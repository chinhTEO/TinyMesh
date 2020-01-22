cmake_minimum_required(VERSION 3.0.0)

if(BUILD_TEST)
    add_subdirectory(googletest)
    add_subdirectory(nb_test)
    add_subdirectory(pt-1.4)
endif()