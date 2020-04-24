cmake_minimum_required(VERSION 3.8)

set(This AstarTests)

project(${This} C CXX) 
set(Sources
AstarTests.cpp
)
set(Headers 
Wall.hpp
heuristic.hpp
Agent.hpp
porting.hpp
)
add_executable(${This} ${Sources})

target_link_libraries(${This} PUBLIC
    gtest_main
    Astar
)

add_test(
    NAME ${This}
    COMMAND ${This}
)