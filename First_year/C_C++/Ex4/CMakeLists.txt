cmake_minimum_required(VERSION 3.19)
project(ex4_dor_peleg C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(ex4_dor_peleg
        hashmap.c
        main.c
        pair.c
#        test_suite.c
        vector.c)
