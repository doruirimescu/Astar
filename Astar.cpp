#include <iostream>
#include <vector>
#include <string>
using namespace std;


typedef struct
{/* Used for returning coordinate: x,y and cost c triples */
    int x, y, c;
}xyc;

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
                                            goalX(gx), goalY(gy),label(l){}
        int getX()const{ return X; }
        int getY()const{ return Y; }
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
                goalY<<")"<<" heuristic: "<<getH()<< endl;
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
            MAPPGridState( vector<Agent> *agents, vector<Wall> *walls, 
                        int xsize, int ysize )
            {
                this->agents = *agents;
                agents->clear();
                this->walls = *walls;
                walls->clear();
                this->xsize = xsize;
                this->ysize = ysize;
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

            void succCoords( vector<xyc> &ret, int x, int y )
            {/* 
              * Returns a vector of (x,y,c) possible sucessor coordinates.
              */ 
                xyc candidates[ 5 ] = { {x, y, 0}, {x + 1, y, 1}, {x - 1, y, 1}, 
                                    {x, y + 1, 1}, {x, y - 1, 1} };
                for( int i = 0; i < 5; ++i )
                {
                    if( !hasWallAt( candidates[ i ].x, candidates[ i ].y ) )
                    {
                        ret.push_back( candidates[ i ] );
                    }
                }
            }
            void show() const
            {/* 
             * Print agents
             */ 
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
                    if( ! (this->agents.at(i) == a.agents.at(i)) )
                    {
                        return false;
                    }
                }
                return true;
            }
        vector<Agent>agents;
        vector<Wall>walls;
        int xsize, ysize;
};


int main()
{
    Agent agent_1(2,2, 10,10,"Agent 1");
    Agent agent_2(2,2, 7,5,"Agent 2");
    Agent agent_3(2,4, 3,4,"Agent 3");
    Agent agent_4(2,5, 1,1,"Agent 4");
    Agent agent_5(2,6, 10,10,"Agent 5");

    vector<Agent> agents;
    agents.push_back(agent_1);
    agents.push_back(agent_3);

    vector<Wall> walls = { Wall(0,0), Wall(10,11) };
    MAPPGridState grid( &agents, &walls, 10, 10);
    agents.push_back(agent_1);
    agents.push_back(agent_3);
    
    MAPPGridState grid2(&agents,&walls,10,10);
    /* Test equality of states */
    cout<< (grid == grid2)<<endl;

    return 0;
}