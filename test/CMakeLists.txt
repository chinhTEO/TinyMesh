cmake_minimum_required(VERSION 3.0.0)

set(utest dev_utest)

if (CMAKE_VERSION VERSION_LESS 2.8.11)
  include_directories("${gtest_SOURCE_DIR}/include")
endif()

include_directories("${CMAKE_SOURCE_DIR}/dev")

enable_testing()

SET(sourcesUtest
    dev/tyheap_utest.cpp)

add_executable(${utest} ${sourcesUtest})
target_link_libraries(${utest} ${this} gtest_main gmock_main tymeshdev)

add_test(NAME ${utest} 
        COMMAND ${utest})