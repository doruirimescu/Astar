#pragma once
#include "MAPPGridState.hpp"
#include "porting.hpp"
#include <algorithm>
using namespace porting;

namespace Astar
{
    inline unsigned int mapRetrieve(const unordered_map<MAPPGridState, unsigned int> &m,
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
    vector<MAPPGridState> astar( MAPPGridState &grid );
    
};