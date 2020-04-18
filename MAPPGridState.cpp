#include "MAPPGridState.hpp"

MAPPGridState::MAPPGridState( std::vector<Agent>&agents, unsigned int xsize, unsigned int ysize, unsigned int cost )
{
    this->agents =agents;
    this->xsize  = xsize;
    this->ysize  = ysize;
    numberAgents = this->agents.size();

    /* Caclulate current heuristic by summing up agents' heuristics */
    currentHeuristic = 0;
    for( const auto &a : agents )
    {
        currentHeuristic += a.getH();
    }
    currentCost = cost;
}
void MAPPGridState::succCoords( std::vector<Agent> &ret, const Agent &a ) const
{  /* 
    * Take an Agent, move it right, left, up, down, and return
    * the new std::vector of Agents. But check for border and wall
    * collisions.
    */ 
    int x = a.getX();
    int y = a.getY();

    typedef struct
    {/* Used for returning coordinate: x,y */
        int x, y;
    }xy;
    xy candidates[ 4 ] = { {x + 1, y}, {x - 1, y}, {x, y + 1}, {x, y - 1} };
    
    for( int i = 0; i < 4; ++i )
    {
        /* Check that borders are not exceeded */
        if( candidates[i].x >=0 && candidates[i].x < (int)xsize &&
            candidates[i].y >=0 && candidates[i].y < (int)ysize &&
            hasWallAt( candidates[ i ].x, candidates[ i ].y ) == false )
        {
            ret.emplace_back( Agent( candidates[ i ].x, candidates[ i ].y, 
                            a.getGoalX(), a.getGoalY(), a.getLabel() ) );
        }
    }
}

bool MAPPGridState::goodSuccessor( const std::vector<Agent> &successor )
{
    /*
     * If the new successor is valid (no two agents are at the same coords)
     */ 
    unsigned int len = agents.size();
    if( len != successor.size() )
    {
        throw "Successor state has a different number of agents"
                        "than the current state !!!";
    }
    for( unsigned int i = 0; i < len; ++i )
    {
        for( unsigned int j = i + 1; j < len; ++j )
        {
            if( i!=j && sameCoord(successor[i], successor[j]) )
            {/* Double occupancy */
                return false;
            }
        }
    }
    return true;
}

std::vector<MAPPGridState> MAPPGridState::successors()
{
    /*
     * Return the std::vector of successor states
     */ 
    std::vector<Agent> newCoords[numberAgents];
    std::vector<MAPPGridState> newStates;
    
    /* There cannot be more than 4 new states (up, down, left, right) */
    newStates.reserve(4);

    for( unsigned int i = 0; i < numberAgents; ++i )
    {
        /* We can get maximum 4 new coordinates. */
        newCoords[i].reserve(4); 
    }
    unsigned int ctr = 0;
    for( const auto &agent : agents )
    {/* Get possible new coordinates of each agent */
        succCoords( newCoords[ctr], agent );
        ctr++;
    }
    for( unsigned int i = 0; i < numberAgents; ++i )
    {
        /* Create a new state, by copying the current one and 
            replacing the corresponding agent with the new candidate */
        for( unsigned int j = 0; j < newCoords[ i ].size(); ++j )
        {
            /* Make a copy of the agent whose position will be modified */
            Agent tmp    = agents.at(i);

            /* Now, the agents std::vector holds the successor candidate position */
            agents.at(i) = newCoords[ i ][ j ];
            
            if( goodSuccessor(agents) )
            {
                /* Calculate the heuristic sum */
                unsigned int heurSum = 0;
                for( const auto &agent : agents )
                {
                    heurSum += agent.getH();
                }
                /* Each new successor increases the current G cost by one */
                newStates.emplace_back( MAPPGridState( agents, xsize, ysize, currentCost + 1 ) );
            }
            else
            {/* Not a valid successor */
            }
            /* Retrieve modified agents to current value */
            agents.at(i) = tmp;
        }
    }
    return newStates;
}
void MAPPGridState::show()const
{
   /* 
    * Print state information
    */ 
    std::cout << std::endl << "--------PRINTING STATE--------" << std::endl << std::endl;
    for( const auto &i : agents )
    {
        i.show();
    }
    std::cout << "G  " << currentCost <<" H: " << currentHeuristic << " F: " << 
              this->getF() << std::endl;
}
bool MAPPGridState::operator ==( const MAPPGridState &a)const
{
   /*
    * Two states are equal if their agents' respective coordinates
    * are identical.
    */
    for( unsigned int i = 0; i < agents.size(); ++i )
    {
        if( !(this->agents.at(i) == a.agents.at(i)) )
        {
            return false;
        }
    }
    return true;
}

