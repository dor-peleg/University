cmake_minimum_required(VERSION 3.19)
project(ex5_dor_peleg)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(ex5_dor_peleg
        Matrix.cpp
        Matrix.h
        Activation.cpp Dense.cpp MlpNetwork.cpp
        main.cpp)
