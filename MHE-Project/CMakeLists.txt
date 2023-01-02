cmake_minimum_required(VERSION 3.20)
project(Source_Files/MHE_Project)

set(CMAKE_CXX_STANDARD 20)

add_executable(MHE Source_Files/main.cpp
        Source_Files/nonogram_functions.cpp
        Header_Files/nonogram_functions.h
        Source_Files/nonogram_algorithms.cpp
        Header_Files/nonogram_algorithms.h
        Source_Files/nonogram_help_functions.cpp
        Header_Files/nonogram_help_functions.h
        Source_Files/task1.cpp
        Header_Files/task1.h Source_Files/genetic_algorithm.cpp)
