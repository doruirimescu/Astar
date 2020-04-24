#include "Agent.hpp"

void Agent::show() const
{/* Print agent information */
    OUTPUT << label << " at:(" << X << ", " << Y << ")" << " goal: (" << goalX <<
    ", "<< goalY << ")" << " heuristic: " << getH() << endline;
}

bool Agent::operator == (const Agent &a)const
{/* Used for comparing states */
    if( this->X == a.getX() && this->Y == a.getY() )
    {
        return true;
    }
    return false;
}
