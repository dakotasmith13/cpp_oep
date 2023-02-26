cmake_minimum_required(VERSION 3.8)
project(M2OEP)

set(CMAKE_CXX_STANDARD 14)

add_executable(M2OEP main.cpp Stock.h Stock.cpp Portfolio.h Portfolio.cpp Login.h Login.cpp)
add_executable(test testing.cpp Stock.h Stock.cpp Portfolio.h Portfolio.cpp Login.h Login.cpp)
