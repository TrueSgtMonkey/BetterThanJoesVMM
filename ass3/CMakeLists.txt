cmake_minimum_required(VERSION 3.20)
project(ass3)

set(CMAKE_CXX_STANDARD 14)

add_executable(ass3 main.cpp Page.cpp PageTable.cpp PageDirectory.cpp vmm.cpp)
