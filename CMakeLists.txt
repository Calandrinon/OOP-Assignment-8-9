cmake_minimum_required(VERSION 3.16)
project(OOP_Assignment_8)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-g -O0 -Wall -Werror -fprofile-arcs -ftest-coverage")
set(CMAKE_CXX_OUTPUT_EXTENSION_REPLACE 1)

include_directories(.)

add_executable(OOP_Assignment_8
        main.cpp
        myexceptions.h
        recording.cpp
        recording.h
        repository.cpp
        repository.h
        service.cpp
        service.h
        tests.cpp
        tests.h
        ui.cpp
        ui.h
        validator.cpp
        validator.h
        string_functions.cpp
        string_functions.h)

