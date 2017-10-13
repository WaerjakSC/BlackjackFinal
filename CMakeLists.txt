cmake_minimum_required(VERSION 3.8)
project(BlackjackFinal)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES main.cpp Functions.cpp Functions.h)
add_executable(BlackjackFinal ${SOURCE_FILES})