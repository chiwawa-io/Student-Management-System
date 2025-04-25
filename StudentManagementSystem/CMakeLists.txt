cmake_minimum_required(VERSION 3.29)
project(StudentManagementSystem)

set(CMAKE_CXX_STANDARD 20)

add_executable(StudentManagementSystem main.cpp
        Person.h
        Student.h
        Course.h)
