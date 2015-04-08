cmake_minimum_required(VERSION 3.1)
project(npuzzle)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O3")

set(SOURCE_FILES
    src/Parser.class.cpp
    src/Puzzle.class.cpp
    src/Utils.class.cpp
    src/Node.class.cpp
    src/main.cpp)

include_directories(inc)

add_executable(npuzzle ${SOURCE_FILES})
