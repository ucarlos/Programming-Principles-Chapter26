cmake_minimum_required(VERSION 3.19)
project(Chapter26)

set(CMAKE_CXX_STANDARD 17)

add_executable(SimpleBinarySearch Simple_Binary_Search.cc)
add_executable(BinarySearch Binary_Search.cc)

# Chapter Problems:
add_executable(Chapter26_Drill01 Chapter26_Drill01.cc Chapter26_Drill.cc)
add_executable(Chapter26_Drill03 Chapter26_Drill03.cc Chapter26_Drill.cc)
add_executable(Chapter26_Drill04 Chapter26_Drill04.cc Chapter26_Drill.cc)
add_executable(Chapter26_12 Chapter26_12.cc)
add_executable(Chapter26_13 Chapter26_13.cc)
