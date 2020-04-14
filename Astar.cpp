#include <iostream>
#include <vector>
#include <string>
using namespace std;


namespace heuristic
{
    /*
     * A collection of heuristic functions (add more if needed) 
     */ 
    static int h( int x, int y, int goalX, int goalY )
    {   /* Manhattan distance */
        return abs(goalX-x) + abs(goalY-y);
    }
}

class Wall
{
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
    /*
    *   An agent is defined by its x and y initial coordinates in the grid, and
    *   a goal position in the grid. An agent can calculate is own heuristic.
    *   An agent also has a label, for identification
    */
    public:
        Agent(int x, int y, int gx, int gy, string l): X(x), Y(y), 
                                            goalX(gx), goalY(gy), label(l){}
        int getX()const{ return X; }
        int getY()const{ return Y; }

        int getGoalX()const{ return goalX; }
        int getGoalY()const{ return goalY; }

        string getLabel()const{ return label; }

        void setX(int x)
        {
            X = x;
        }
        void setY(int y)
        {
            Y = y;
        }
        void setGoal(int x, int y)
        {
            goalX = x;
            goalY = y;
        }
        int getH()const
        {
            return heuristic::h( X, Y, goalX, goalY );
        }
        void setCost( int c ){ cost = c; }
        int getCost() const { return cost; };

        bool operator ==(const Agent &a)
        {/* Used for comparing states */
            if( this->X == a.getX() && this->Y == a.getY() )
            {
                return true;
            }
            return false;
        }
        void show() const
        {
            cout<<label<<" at:("<<X<<", "<<Y<<")"<<" goal: ("<<goalX<<", "<<
                goalY<<")"<<" heuristic: "<<getH()<<" cost: "<<cost<< endl;
        }
        
    private:
        int X, Y;
        int goalX, goalY;
        int cost = 0;
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
            MAPPGridState( vector<Agent>agents, vector<Wall>walls, 
                        int xsize, int ysize )
            {
                this->agents = agents;
                this->walls = walls;
                this->xsize = xsize;
                this->ysize = ysize;
                numberAgents = this->agents.size();
            }
            bool hasWallAt( int x, int y )
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

            void succCoords( vector<Agent> &ret, const Agent &a )
            {/* 
              * Returns a vector of Agents, for each possible move.
              */ 
                int x = a.getX();
                int y = a.getY();
                typedef struct
                {/* Used for returning coordinate: x,y and cost c triples */
                    int x, y, c;
                }xyc;
                xyc candidates[ 4 ] = { {x + 1, y, 1}, {x - 1, y, 1}, 
                                    {x, y + 1, 1}, {x, y - 1, 1} };
                for( int i = 0; i < 4; ++i )
                {
                    if( !hasWallAt( candidates[ i ].x, candidates[ i ].y ) )
                    {
                        ret.push_back( Agent( candidates[ i ].x, candidates[ i ].y, 
                                       a.getGoalX(), a.getGoalY(), a.getLabel() ) );
                        ret.back().setCost(candidates[i].c);
                    }
                }
            }

            bool sameCoord(const Agent &a, const Agent &b)
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
                /*TODO
                 * If the new positions are representing a good successor state
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

            void successors(vector<MAPPGridState> &newStates )
            {
                /*
                 * Should return the list of successor states, together with the associated cost.
                 */ 
                vector<Agent> newCoords[numberAgents];
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
                        agentsCopy.at(i) = newCoords[ i ][ j ];
                        if( goodSuccessor(agentsCopy) )
                        {
                            newStates.push_back( MAPPGridState( agentsCopy, walls, xsize, ysize ) );
                        }
                        else
                        {
                            cout<<"!!!!!!!!!!!THIS IS NOT A VALID SUCCESSOR";
                        }
                        
                    }
                }
            }
            void show() const
            {/* 
             * Print agents
             */ 
                cout<<endl<<"--------PRINTING STATE--------"<<endl<<endl;
                for( const auto i : agents )
                {
                    i.show();
                }
            }
            bool operator ==( MAPPGridState &a)
            {
                /*
                *  Two states are equal if their agents' respective coordinates
                *  are identical.
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
        vector<Wall>walls;
        int xsize, ysize, numberAgents;
};

int main()
{
    Agent agent_1(2,2, 10,10,"Agent 1");
    Agent agent_2(3,2, 7,5,"Agent 2");
    Agent agent_3(4,3, 3,4,"Agent 3");
    Agent agent_4(5,5, 1,1,"Agent 4");
    Agent agent_5(6,6, 10,10,"Agent 5");

    vector<Agent> agents;
    agents.push_back(agent_1);
    agents.push_back(agent_2);

    vector<Wall> walls = { Wall(0,0), Wall(10,11) };
    MAPPGridState grid( agents, walls, 10, 10);

    cout<<"↓Original state↓";
    grid.show();
    cout<<"↓Successor states↓"<<endl;
    vector<MAPPGridState> newStates;
    grid.successors(newStates);
    for( const auto state : newStates )
    {
        state.show();
    }
    return 0;
}