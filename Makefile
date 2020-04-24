output: main.o Astar.o MAPPGridState.o Agent.o heuristic.o
	g++ main.o Astar.o MAPPGridState.o Agent.o heuristic.o -o output

main.o: main.cpp
	g++ -c main.cpp

Astar.o: Astar.cpp Astar.hpp
	g++ -c Astar.cpp

MAPPGridState.o: MAPPGridState.cpp MAPPGridState.hpp
	g++ -c MAPPGridState.cpp

Agent.o: Agent.cpp Agent.hpp
	g++ -c Agent.cpp

heuristic.o: heuristic.cpp heuristic.hpp
	g++ -c heuristic.cpp
clean:
	rm main.o Astar.o MAPPGridState.o Agent.o heuristic.o