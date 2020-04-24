# Description
**Programming language: C++11 and newer**

Multi-agent path planning (MAPP) using the A* algorithm. This implementation is based on the [Aalto CS-E4800 Artificial Intelligence](https://mycourses.aalto.fi/course/view.php?id=24364) course, where I was a teaching assistant.

The problem comprises of a two-dimensional grid, where there are set of agents (each with its own location and goal) and optionally, a set of walls representing locations where no agent can be.

## File descriptions
| Class            | Description                                                                          | Location  |
| ---------------- | ------------------------------------------------------------------------------------ |-----------|
| Wall             | A grid location where no agent can be located at any time. _Walls should not be added at any agent's goal coordinates._                            | Wall.hpp  |
| Agent            | An intelligent agent, moving in a two-dimensional grid from a starting position towards its goal (final position). In multi-agent problems such as this one, _there can be more than one single agent pursuing its goal at any time in the grid_.| Agent.hpp, Agent.cpp |
| MAPPGridState    | The state-space representation of a grid comprises of a vector of MAPPGridStates, each such state representing a collection of agents and their current positions on the grid, together with the total cost which took to reach the state, and the _state heuristic -the estimated cost to reach the goal state-_. The cost of moving from one state to the successor (next) state is always 1, since in this representation only one agent can move per state transition. The state heuristic is computed as the sum of all individual heuristics of the agents. | MAPPGridState.hpp, MAPPGridState.cpp |

| Namespace        | Description                                                                          | Location  |
| ---------------- | ------------------------------------------------------------------------------------ |-----------|
| heuristic        | Contains a function that computes the heuristic of an agent, ie. the estimate of the distance from the current location to the goal. It is enouraged to add more heuristics -if required by the problem- in this namespace. | heuristic.hpp, heuristic.cpp |
| Astar            | Contains the actual A* algorithm, used to search the state-space and retrieve the best state trajectory that solves the problem. | Astar.hpp, Astar.cpp |

| File             | Description                                                                          |
| ---------------- | ------------------------------------------------------------------------------------ |
| porting.hpp      | For easily porting the standard library-based implementation to other frameworks (such as QT). |
| main.cpp         | For demonstrating the usage of the Astar program in a practical scenario. |
| test/AstarTests.cpp         | Unit tests that shall pass after any modification that is made to the program. |

# Compile and run
In order to compile and run the program, run the following commands:

```make```

```./output```

```make clean```

# Google Test
In order to run the unit tests, run the following commands from the Astar folder.

```cmake --build build --config Debug --target all -- -j 6```

```cd build```

```ctest -j6 -C Debug -T test --output-on-failure```

Or, you can open the project with Visual Studio Code and run the tests from the status bar, CMake Tools extension is needed.

For more details on Google Test with VS Code, watch : https://youtu.be/Lp1ifh9TuFI
