#pragma once

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