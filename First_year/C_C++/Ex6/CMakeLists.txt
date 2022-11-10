cmake_minimum_required(VERSION 3.19)
project(ex6_dor_peleg)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(ex6_dor_peleg
        helpers.h
#        presubmit.cpp
        vl_vector.cpp
        vl_vector.h
        vl_string.cpp vl_string.h
        ex6_bonus_tests.cpp)
