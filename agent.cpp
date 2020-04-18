#include "agent.hpp"

void Agent::show() const
{/* Print agent information */
    std::cout << label << " at:(" << X << ", " << Y << ")" << " goal: (" << goalX <<
    ", "<< goalY << ")" << " heuristic: " << getH() << std::endl;
}

bool Agent::operator == (const Agent &a)const
{/* Used for comparing states */
    if( this->X == a.getX() && this->Y == a.getY() )
    {
        return true;
    }
    return false;
}
