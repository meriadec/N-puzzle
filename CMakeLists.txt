cmake_minimum_required(VERSION 3.1)
project(N_puzzle)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    src/Parser.class.cpp
    src/main.cpp)

include_directories(inc)

add_executable(N_puzzle ${SOURCE_FILES})