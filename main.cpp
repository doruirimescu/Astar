#include <unordered_map>
#include <queue>
#include<algorithm>

#include"wall.hpp"
#include "heuristic.hpp"
#include"agent.hpp"
#include "MAPPGridState.hpp"

std::vector<Wall> MAPPGridState::walls = {};

int main()
{
    /* Create walls */
    MAPPGridState::walls.push_back(Wall(1,1));
    MAPPGridState::walls.push_back(Wall(2,2));

    Agent agent_1(0,0, 10,0,"Agent 1");
    Agent agent_2(0,1, 7,5,"Agent 2");

    std::vector<Agent> agents;

    agents.emplace_back(agent_1);
    agents.emplace_back(agent_2);

    MAPPGridState grid( agents, 100, 100, 0 );
    std::cout<<"↓Original state↓";
    grid.show();
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
            unsigned int mcn = 10000, mcs = 10000;
            if ( minCost.find(n) != minCost.end() )
            {
                
                mcn = minCost.find(n)->second;
            }
            if ( minCost.find(succ) != minCost.end() )
            {
                mcs = minCost.find(succ)->second;
            }
            if( mcn + 1 < mcs )
            {
                minCost.insert( {succ, mcn + 1} );
                succ.currentCost = mcn + 1;
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
    while( !(predecessors.find(n)->second == grid))
    {
        n = predecessors.find(n)->second;
        results.emplace_back(n);
    }
    n = predecessors.find(n)->second;
    results.emplace_back(n);

    std::reverse(results.begin(), results.end());
    for( auto iter = results.begin(); iter < results.end(); ++iter )
    {
        iter->show();
    }

    std::cout<<results.size();
    return 0;
}
