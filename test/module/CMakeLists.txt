cmake_minimum_required(VERSION 3.0.0)

set(utest module_utest)

if(BUILD_TEST)
  add_definitions(-DUTEST)
endif()

if (CMAKE_VERSION VERSION_LESS 2.8.11)
  include_directories("${gtest_SOURCE_DIR}/include")
endif()

enable_testing()

SET(sourcesUtest
    ibc_utest.cpp
    abc_utest.cpp
)

add_executable(${utest} ${sourcesUtest})
target_link_libraries(${utest} ${this} gtest_main gmock_main tymeshsys tymeshnet tymeshdev tymeshmodule)

add_test(NAME ${utest} 
        COMMAND ${utest})