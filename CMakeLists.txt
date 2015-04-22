cmake_minimum_required(VERSION 3.1)
project(npuzzle)
set(EXECUTABLE_NAME "npuzzle")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O3 -Wall -Wextra -Werror -pedantic")

set(SFML_INCLUDE_DIR $ENV{HOME}/.brew/include)
set(SFML_ROOT $ENV{HOME}/.brew/lib)
set(CMAKE_MODULE_PATH $ENV{HOME}/.brew/Cellar/sfml/2.2/share/SFML/cmake/Modules)

find_package(SFML 2 REQUIRED system window graphics audio network)

set(SOURCE_FILES
    src/Parser.class.cpp
    src/Puzzle.class.cpp
    src/Utils.class.cpp
    src/Graphic.class.cpp
    src/Node.class.cpp
    src/main.cpp)

include_directories(inc)

add_executable(${EXECUTABLE_NAME} ${SOURCE_FILES})

if(SFML_FOUND)
  include_directories(${SFML_INCLUDE_DIR})
  target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES})
endif()
