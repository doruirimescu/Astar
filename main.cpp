
#include "astar.hpp"
#include"wall.hpp"
#include "heuristic.hpp"
#include"agent.hpp"
#include "MAPPGridState.hpp"
#include "porting.hpp"

vector<Wall> MAPPGridState::walls = {};

int main()
{
    /* Create walls */
    MAPPGridState::walls.push_back(Wall(0, 0));
    MAPPGridState::walls.push_back(Wall(0, 5));

    Agent agent_1(0,0,  10,10,  "Agent 1");
    Agent agent_2(0,5,  15,17,  "Agent 2");
    vector<Agent> agents;

    agents.emplace_back(agent_1);
    agents.emplace_back(agent_2);

    MAPPGridState grid( agents, 100, 100, 0 );

    
    OUTPUT << "↓Original state↓";
    grid.show();
    vector<MAPPGridState> results = Astar::astar(grid);
    for( auto iter = results.begin(); iter < results.end(); ++iter )
    {
        iter->show();
    }
    
    return 0;
}