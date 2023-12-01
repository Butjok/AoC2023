cmake_minimum_required(VERSION 3.19)
project(AoC2023)

set(CMAKE_CXX_STANDARD 20)

add_executable(AoC2023 Day.hpp main.cpp FileSystem.hpp FileSystem.cpp Day1.cpp)