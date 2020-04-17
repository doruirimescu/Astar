#include "Astar.cpp"
#include <unordered_map>
#include <queue>
#include<algorithm>

int main()
{
    // Create walls 
    MAPPGridState::walls.push_back(Wall(1,1));
    MAPPGridState::walls.push_back(Wall(2,2));

    Agent agent_1(0,0, 10,0,"Agent 1");
    Agent agent_2(0,1, 7,5,"Agent 2");
    Agent agent_3(4,3, 3,4,"Agent 3");
    Agent agent_4(5,5, 1,1,"Agent 4");
    Agent agent_5(6,6, 10,10,"Agent 5");

    vector<Agent> agents;
    //! Reserve the number of agents we will emplace_back
    agents.reserve(2);

    agents.emplace_back(agent_1);
    agents.emplace_back(agent_2);

    MAPPGridState grid( agents, 100, 100, 0 );
    cout<<"↓Original state↓";
    grid.show();
    vector<MAPPGridState> newStates = grid.successors();

    /* A* algo */
    priority_queue<MAPPGridState, vector<MAPPGridState>, CompareStates> Q;
    Q.push( grid );
    bool going = true;
    MAPPGridState n = grid;
    unordered_map<MAPPGridState, MAPPGridState, StateHasher> mymap;

    unordered_map<MAPPGridState, unsigned int, StateHasher> minCost;

    minCost.insert({n,0});
    while( !Q.empty() && going )
    {
        n = Q.top();
        Q.pop();
        for( auto &succ : n.successors() )
        { 
            /* Min cost */
            unsigned int mcn = 10000, mcs = 10000;
            if ( minCost.find(n) != minCost.end() )
            {
                
                mcn = minCost.find(n)->second;
            }
            if ( minCost.find(succ) != minCost.end() )
            {
                mcs = minCost.find(succ)->second;
            }
            if( mcn + 1 < mcs )
            {
                minCost.insert( {succ, mcn + 1} );
                succ.currentCost = mcn + 1;
                Q.push(succ);
                mymap.insert({succ,n});
            }
        }
        if( n.getH() == 0 )
        {
            going = false;
        }
        if( going == false )
        {
            cout<<"Found a result"<<endl;
        }
    }
    
    vector<MAPPGridState> results;
    results.reserve(10);

    results.emplace_back(n);
    while( !(mymap.find(n)->second == grid))
    {
        n = mymap.find(n)->second;
        results.emplace_back(n);
    }
    n = mymap.find(n)->second;
    results.emplace_back(n);
    std::reverse(results.begin(), results.end());

    for( auto iter = results.begin(); iter < results.end(); ++iter )
    {
        iter->show();
    }
    cout<<results.size();
    return 0;
}
