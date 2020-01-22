cmake_minimum_required(VERSION 3.1.3)

set(utest mutiple_array_definition)

SET(sourcesUtest
    main.c
    array_1.c
    array_2.c
    array_3.c
    array.c
    array.h
)

add_executable(${utest} ${sourcesUtest})


