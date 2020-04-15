#include <iostream>
#include <vector>
#include <string>

using namespace std;

namespace heuristic
{
    /*
     * A collection of heuristic functions (add more if needed) 
     */ 
    static inline unsigned int h( int x, int y, int goalX, int goalY )
    {   /* Manhattan distance */
        return abs(goalX - x) + abs(goalY - y);
    }
}

class Wall
{
    /*
    *   A wall represents a location where an agent is not allowed to be
    */
    public:
        Wall(int x, int y)
        {
            this->x = x;
            this->y = y;
        }
        int getX()const{ return x; }
        int getY()const{ return y; }
    private:
        int x, y;
};

class Agent
{
    /**
    *   An agent is defined by its x and y initial coordinates in the grid, and
    *   a goal position in the grid. An agent can calculate is own heuristic.
    *   An agent also has a label, for identification
    */

    public:
        Agent(int x, int y, int gx, int gy, string l): X(x), Y(y), 
                                            goalX(gx), goalY(gy), label(l){}
        int getX() const { return X; }
        int getY() const { return Y; }

        int getGoalX() const { return goalX; }
        int getGoalY() const { return goalY; }

        string getLabel() const { return label; }

        void setX(int x) { X = x; }
        void setY(int y) { Y = y; }

        /* Returns agent's heuristic h value */
        int getH() const { return heuristic::h(X, Y, goalX, goalY); }

        bool operator == (const Agent &a)
        {/* Used for comparing states */
            if( this->X == a.getX() && this->Y == a.getY() )
            {
                return true;
            }
            return false;
        }
        void show() const
        {/* Print agent information */
            cout<<label<<" at:("<<X<<", "<<Y<<")"<<" goal: ("<<goalX<<", "<<
                goalY<<")"<<" heuristic: "<<getH()<<endl;
        }
        
    private:
        int X, Y;
        int goalX, goalY;
        string label;
};

class MAPPGridState
{
    /*
    *   The grid state represents the actual state of the grid. It needs a list
    *   of agents, a list of wall positions, the x size of the grid and the
    *   y size of the grid.
    */
    public:
            MAPPGridState( vector<Agent>agents, unsigned int xsize, unsigned int ysize, unsigned int cost )
            {
                this->agents = agents;
                this->xsize  = xsize;
                this->ysize  = ysize;
                numberAgents = this->agents.size();
                currentCost  = cost;

                /* Caclulate current heuristic by summing up agents' heuristics */
                currentHeuristic = 0;
                for( const auto a : agents )
                {
                    currentHeuristic += a.getH();
                }
            }
            inline unsigned int getF() const
            {
                return currentCost + currentHeuristic;
            }
            static bool hasWallAt( int x, int y )
            {
                /*
                * Check if there are walls at specific location
                */
                for( const auto i : walls )
                {
                    if( i.getX() == x && i.getY() == y )
                    {
                        return true;
                    }
                }
                return false;
            }

            void succCoords( vector<Agent> &ret, const Agent &a ) const
            {/* 
              * Take an Agent, move it right, left, up, down, and return
              * the new vector of Agents. But check for border and wall
              * collisions.
              */ 
                int x = a.getX();
                int y = a.getY();
                typedef struct
                {/* Used for returning coordinate: x,y */
                    int x, y;
                }xy;
                xy candidates[ 4 ] = { {x + 1, y}, {x - 1, y}, 
                                    {x, y + 1}, {x, y - 1} };
                for( int i = 0; i < 4; ++i )
                {
                    /* Check that borders are not exceeded */
                    if( candidates[i].x >=0 && candidates[i].x < xsize &&
                        candidates[i].y >=0 && candidates[i].y < ysize &&
                        hasWallAt( candidates[ i ].x, candidates[ i ].y ) == false )
                    {
                        ret.push_back( Agent( candidates[ i ].x, candidates[ i ].y, 
                                       a.getGoalX(), a.getGoalY(), a.getLabel() ) );
                    }
                }
            }

            inline bool sameCoord(const Agent &a, const Agent &b)
            {
                /*
                 * Test if two agents have the same coordinates 
                 */ 
                if( ( a.getX() == b.getX() ) && ( a.getY() == b.getY() ) )
                {
                    return true;
                }
                return false;
            }
            bool goodSuccessor( const vector<Agent> &successor )
            {
                /*
                 * If the new successor is valid (no two agents are at the same coords)
                 */ 
                int len = agents.size();
                for( int i = 0; i < len; ++i )
                {
                    for( int j = i + 1; j < len; ++j )
                    {
                        if( i!=j && sameCoord(successor[i], successor[j]) )
                        {/* Double occupancy */
                            return false;
                        }
                    }
                }
                return true;
            }

            vector<MAPPGridState> successors()
            {
                /*
                 * Return the vector of successor states
                 */ 
                vector<Agent> newCoords[numberAgents];
                vector<MAPPGridState> newStates;
                int ctr = 0;
                for( const auto agent : agents )
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
                        /* Copy original agents vecotr */
                        vector<Agent> agentsCopy(agents);
                        
                        /* Replace the newly moved agent */
                        agentsCopy.at(i) = newCoords[ i ][ j ];

                        /* Calculate the heuristic sum */
                        unsigned int heurSum = 0;
                        for( unsigned int a = 0; a < numberAgents; ++a )
                        {
                            heurSum += agentsCopy[a].getH();
                        }

                        if( goodSuccessor(agentsCopy) )
                        {
                            /* Each new successor increases the current G cost by one */
                            newStates.push_back( MAPPGridState( agentsCopy, xsize, ysize, currentCost + 1 ) );
                        }
                        else
                        {/* Not a valid successor */
                        }
                    }
                }
                return newStates;
            }
            void show() const
            {
                /* 
                * Print state information
                */ 
                cout<<endl<<"--------PRINTING STATE--------"<<endl<<endl;
                for( const auto i : agents )
                {
                    i.show();
                }
                cout<<"G  "<<currentCost<<" H: "<<currentHeuristic<<" F: "<<this->getF()<<endl;
            }
            bool operator ==( MAPPGridState &a)
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
        vector<Agent>agents;
        static vector<Wall>walls;
        unsigned int xsize, ysize, numberAgents, currentCost, currentHeuristic;
};

vector<Wall> MAPPGridState::walls = { };

int main()
{
    // Create walls 
    MAPPGridState::walls.push_back(Wall(1,0));

    Agent agent_1(0,0, 10,10,"Agent 1");
    Agent agent_2(0,1, 7,5,"Agent 2");
    Agent agent_3(4,3, 3,4,"Agent 3");
    Agent agent_4(5,5, 1,1,"Agent 4");
    Agent agent_5(6,6, 10,10,"Agent 5");

    vector<Agent> agents;
    agents.push_back(agent_1);
    agents.push_back(agent_2);

    MAPPGridState grid( agents, 10, 10,0 );

    cout<<"↓Original state↓";
    grid.show();
    cout<<endl<<"↓Successor states↓"<<endl;
    vector<MAPPGridState> newStates = grid.successors();

    for( auto i:newStates)
    {
        i.show();
        vector<MAPPGridState> nS = i.successors();
        for( auto j:nS)
        {
            j.show();
        }
    }
    return 0;
}
