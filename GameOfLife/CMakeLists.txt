cmake_minimum_required(VERSION 3.24)
project(GameOfLife)

include(FetchContent)
set(BUILD_SHARED_LIBS  OFF)
FETCHCONTENT_DECLARE(SFML GIT_REPOSITORY https://github.com/SFML/SFML GIT_TAG 2.6.1)
FETCHCONTENT_MAKEAVAILABLE(SFML)

set(CMAKE_CXX_STANDARD 17)

add_executable(GameOfLife main.cpp StartStopButton.cpp StartStopButton.h Board.cpp Board.h Board.h)

target_link_libraries(GameOfLife sfml-graphics)
