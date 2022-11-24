cmake_minimum_required(VERSION 3.21)
project(iterated_list)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(iterated_list
        iterated_application.cpp
        iterated_application.h
        iterated_list.h
        main.cpp
        z_output.h
        z_work_report.h)
