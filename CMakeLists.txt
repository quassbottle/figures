cmake_minimum_required(VERSION 3.23)
project(figures)

set(CMAKE_CXX_STANDARD 14)

add_executable(figures main.cpp figure.h repository.h)
