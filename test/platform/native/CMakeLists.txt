cmake_minimum_required(VERSION 3.0.0)

set(utest platformnative_utest)

if(BUILD_TEST)
  add_definitions(-DUTEST)
endif()

if (CMAKE_VERSION VERSION_LESS 2.8.11)
  include_directories("${gtest_SOURCE_DIR}/include")
endif()

enable_testing()

SET(sourcesUtest
)

add_executable(${utest} ${sourcesUtest})
target_link_libraries(${utest} ${this} gtest_main gmock_main tymeshdev tymeshnet)

add_test(NAME ${utest} 
        COMMAND ${utest})