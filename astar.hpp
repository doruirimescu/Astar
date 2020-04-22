#pragma once
#include "MAPPGridState.hpp"
#include <unordered_map>
#include <queue>
#include<algorithm>

namespace Astar
{
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
    std::vector<MAPPGridState> astar( MAPPGridState &grid );
    
};