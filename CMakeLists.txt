cmake_minimum_required(VERSION 3.8)

set(This Astar)

project(${This} C CXX)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
enable_testing()

add_subdirectory(googletest)


set(Headers 
    Wall.hpp
    heuristic.hpp
    MAPPGridState.hpp
    Astar.hpp
    porting.hpp
)

set(Sources
    heuristic.cpp
    Agent.cpp
    MAPPGridState.cpp
    Astar.cpp
)
add_library( ${This} STATIC ${Sources} ${Headers} )

add_subdirectory(test)
set_target_properties(${This} PROPERTIES LINKER_LANGUAGE CXX)
