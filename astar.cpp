#include "astar.hpp"
std::vector<MAPPGridState> Astar::astar( MAPPGridState &grid )
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