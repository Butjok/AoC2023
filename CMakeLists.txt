cmake_minimum_required(VERSION 3.19)
project(AoC2023)

set(CMAKE_CXX_STANDARD 20)

add_executable(AoC2023 Day.hpp main.cpp FileSystem.hpp FileSystem.cpp Day1.cpp Day2.cpp Day3.cpp Day4.cpp Day5.cpp Day6.cpp)