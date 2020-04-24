#pragma once
#include "heuristic.hpp"
#include "porting.hpp"
using namespace porting;

class Agent
{
    /**
    *   An agent is defined by its x and y initial coordinates in the grid, and
    *   a goal position in the grid. An agent can calculate is own heuristic.
    *   An agent also has a label, for identification
    */

    public:
        Agent(int x, int y, int gx, int gy, string l): X(x), Y(y), 
                                            goalX(gx), goalY(gy), label(l){};

        int getX() const { return X; };
        int getY() const { return Y; };

        int getGoalX() const { return goalX; };
        int getGoalY() const { return goalY; };

        string getLabel() const { return label; };

        void setX(int x) { X = x; };
        void setY(int y) { Y = y; };

        /* Returns agent's heuristic h value */
        int getH() const { return heuristic::h(X, Y, goalX, goalY); };

        bool operator == (const Agent &a)const;

        void show() const;
        
    private:
        int X, Y;
        int goalX, goalY;
        string label;
};