#include "Astar.cpp"

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
