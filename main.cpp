#include <unordered_map>
#include <queue>
#include<algorithm>

#include"wall.hpp"
#include "heuristic.hpp"
#include"agent.hpp"
#include "MAPPGridState.hpp"

std::vector<Wall> MAPPGridState::walls = {};

inline unsigned int mapRetrieve(const std::unordered_map<MAPPGridState, unsigned int> &m,
                        const MAPPGridState &n)
{
    if ( m.find(n) != m.end() )
    {
        return m.find(n)->second;
    }
    else
    {
        return 10000;
    }
}
std::vector<MAPPGridState> Astar( MAPPGridState &grid)
{
    std::vector<MAPPGridState> newStates = grid.successors();

    /* A* algo */
    std::priority_queue<MAPPGridState, std::vector<MAPPGridState>> Q;
    Q.push( grid );
    
    MAPPGridState n = grid;
    std::unordered_map<MAPPGridState, MAPPGridState> predecessors;
    std::unordered_map<MAPPGridState, unsigned int> minCost;

    minCost.insert({n,0});
    bool going = true;
    while( !Q.empty() && going )
    {
        n = Q.top();
        Q.pop();
        for( auto &succ : n.successors() )
        { 
            /* Min cost */
            unsigned int mcn, mcs;
            mcn = mapRetrieve( minCost, n );
            mcs = mapRetrieve( minCost, succ );

            if( mcn + 1 < mcs )
            {
                minCost.insert( {succ, mcn + 1} );
                succ.setCost( mcn + 1 );
                Q.push(succ);
                predecessors.insert( {succ, n} );
            }
        }
        if( n.getH() == 0 )
        {
            going = false;
            std::cout<<"Found a result"<<std::endl;
        }
    }
    
    /* std::vector that holds state trajectory */
    std::vector<MAPPGridState> results;
    results.reserve(10);

    results.emplace_back(n);
    while( !(predecessors.find(n)->second == grid) )
    {
        n = predecessors.find(n)->second;
        results.emplace_back(n);
    }
    n = predecessors.find(n)->second;
    results.emplace_back(n);

    std::reverse(results.begin(), results.end());
    return results;
}
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
    std::vector<MAPPGridState> results = Astar(grid);
    for( auto iter = results.begin(); iter < results.end(); ++iter )
    {
        iter->show();
    }
    
    return 0;
}