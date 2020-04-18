#include "heuristic.hpp"

unsigned int heuristic::h( int x, int y, int goalX, int goalY )
{   /* Manhattan distance */
    return abs(goalX - x) + abs(goalY - y);
}
