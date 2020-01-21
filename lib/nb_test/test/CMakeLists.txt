project(utest)
cmake_minimum_required(VERSION 3.1.3)

set(utest nb_test_utest)

SET(sourcesUtest
    utest.h
    nb_test_utest.c
)

add_executable(${utest} ${sourcesUtest})
target_link_libraries(${utest} ${this} nb_test)


if("${CMAKE_C_COMPILER_ID}" STREQUAL "GNU")
  list(FIND CMAKE_C_COMPILE_FEATURES c_std_11 IDX)
  if (${IDX} GREATER -1)
    set_source_files_properties(type_printers.c PROPERTIES
      COMPILE_FLAGS "-std=gnu11")
  endif()
  set_source_files_properties(main.c test.c PROPERTIES
    COMPILE_FLAGS "-Wall -Wextra -Werror -std=gnu89"
  )
elseif("${CMAKE_C_COMPILER_ID}" STREQUAL "Clang")
  set_source_files_properties(main.c test.c PROPERTIES
    COMPILE_FLAGS "-Wall -Wextra -Weverything -Werror -std=gnu89"
  )
elseif("${CMAKE_C_COMPILER_ID}" STREQUAL "MSVC")
  set_source_files_properties(main.c test.c PROPERTIES
    COMPILE_FLAGS "/Wall /WX /wd4514 /wd5045"
  )
else()
  message(WARNING "Unknown compiler '${CMAKE_C_COMPILER_ID}'!")
endif()

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
  set_source_files_properties(test.cpp PROPERTIES
    COMPILE_FLAGS "-Wall -Wextra -Werror -std=gnu++98"
  )
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
  set_source_files_properties(test.cpp PROPERTIES
    COMPILE_FLAGS "-Wall -Wextra -Weverything -Werror -std=gnu++98"
  )
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
  set_source_files_properties(test.cpp PROPERTIES
    COMPILE_FLAGS "/Wall /WX /wd4514 /wd5045"
  )
else()
  message(WARNING "Unknown compiler '${CMAKE_C_COMPILER_ID}'!")
endif()

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
  set_source_files_properties(test11.cpp PROPERTIES
    COMPILE_FLAGS "-Wall -Wextra -Werror -std=c++11"
  )
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
  set_source_files_properties(test11.cpp PROPERTIES
    COMPILE_FLAGS "-Wall -Wextra -Weverything -Werror -std=c++11 -Wno-c++98-compat"
  )
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
  set_source_files_properties(test11.cpp PROPERTIES
    COMPILE_FLAGS "/Wall /WX /wd4514 /wd5045"
  )
else()
  message(WARNING "Unknown compiler '${CMAKE_C_COMPILER_ID}'!")
endif()