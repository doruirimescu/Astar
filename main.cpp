
#include "Astar.hpp"
#include"wall.hpp"
#include "heuristic.hpp"
#include"agent.hpp"
#include "MAPPGridState.hpp"

std::vector<Wall> MAPPGridState::walls = {};

int main()
{
    /* Create walls */
    MAPPGridState::walls.push_back(Wall(1, 5));
    MAPPGridState::walls.push_back(Wall(9, 6));
    MAPPGridState::walls.push_back(Wall(0, 1));
    MAPPGridState::walls.push_back(Wall(9, 10));
    MAPPGridState::walls.push_back(Wall(19,13));

    Agent agent_1(0,0,  10,10,  "Agent 1");
    Agent agent_2(5,5,  15,17,  "Agent 2");
    Agent agent_3(3,8,  19,14,  "Agent 3");
    Agent agent_4(15,12, 1,1,   "Agent 4");

    std::vector<Agent> agents;

    agents.emplace_back(agent_1);
    agents.emplace_back(agent_2);
    agents.emplace_back(agent_3);
    agents.emplace_back(agent_4);

    MAPPGridState grid( agents, 100, 100, 0 );

    
    std::cout<<"↓Original state↓";
    grid.show();
    std::vector<MAPPGridState> results = Astar::astar(grid);
    for( auto iter = results.begin(); iter < results.end(); ++iter )
    {
        iter->show();
    }
    
    return 0;
}