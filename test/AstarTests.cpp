#include"../wall.hpp"
#include"../agent.hpp"
#include"../MAPPGridState.hpp"
#include<gtest/gtest.h>
using namespace std;

vector<Wall> MAPPGridState::walls = {};

struct AstarTests: public ::testing::Test
{
    /* Create some agents for the test */
    Agent agent_1 = Agent(0,0, 10,15,"Agent 1");
    Agent agent_2 = Agent(0,1, 7,5,"Agent 2");
    Agent agent_3 = Agent(4,3, 3,4,"Agent 3");
    Agent agent_4 = Agent(5,5, 1,1,"Agent 4");
    Agent agent_5 = Agent(6,6, 10,10,"Agent 5");
    Agent agent_6 = Agent(0,0, 13,10,"Agent 6");
};
/* Heuristic tests */
TEST_F(AstarTests, HEURISTIC)
{
    EXPECT_EQ( heuristic::h(0,0,0,0), 0);
    EXPECT_EQ( heuristic::h(10,0,0,0), 10);
    EXPECT_EQ( heuristic::h(0,0,0,10), 10);
    EXPECT_EQ( heuristic::h(5,5,0,0), 10);
    EXPECT_EQ( heuristic::h(-10,0,-10,0),0); //(-10 - (-10)) = 0
}
/* Wall tests */
TEST_F(AstarTests, WALL)
{
    Wall w(5, -10);
    EXPECT_EQ(w.getX(), 5 );
    EXPECT_EQ(w.getY(), -10);
    EXPECT_NE(w.getX(),-10);
}

/* Agent tests*/
TEST_F(AstarTests, AGENT_EQUALITY)
{
    EXPECT_EQ(agent_1==agent_1, true);
    EXPECT_EQ(agent_1==agent_6, true);
    EXPECT_EQ(agent_5==agent_6, false);
}

TEST_F(AstarTests, AGENT_SETTERS)
{
    EXPECT_EQ(agent_1 == agent_3, false);
    agent_1.setX(4);
    agent_1.setY(3);
    EXPECT_EQ(agent_1 == agent_3, true);
}

TEST_F(AstarTests, AGENT_GETTERS)
{
    agent_1.setX(5);
    agent_1.setY(5);
    int res = agent_1.getX() + agent_1.getY();
    EXPECT_EQ(res, 10);
    EXPECT_EQ(agent_1.getGoalX() + agent_1.getGoalY(), 25 );
}

TEST_F(AstarTests, AGENT_GETH)
{
    EXPECT_EQ(agent_3.getH(), 2);
    agent_3.setX(agent_3.getX() + 1);
    EXPECT_EQ(agent_3.getH(), 3);
}
/* MAPPGridState tests */
TEST_F(AstarTests, MAPP_getF)
{
    vector<Agent> agents;
    agents.push_back(agent_1);

    MAPPGridState grid( agents, 10, 10, 5 );
    EXPECT_EQ( grid.getF(), 30);

    agents.push_back(agent_2);
    EXPECT_EQ( grid.getF(), 30);

    MAPPGridState grid2( agents, 10, 10, 5 );
    EXPECT_EQ( grid2.getF(), 41);
}

TEST_F(AstarTests, HAS_WALL_AT_1)
{

    MAPPGridState::walls.push_back(Wall(0,0));
    MAPPGridState::walls.push_back(Wall(0,1));
    MAPPGridState::walls.push_back(Wall(1,0));

    EXPECT_EQ( MAPPGridState::hasWallAt(0,0), true);
    EXPECT_EQ( MAPPGridState::hasWallAt(0,1), true);
    EXPECT_EQ( MAPPGridState::hasWallAt(1,0), true);
    EXPECT_EQ( MAPPGridState::hasWallAt(1,1), false);
}

TEST_F(AstarTests, HAS_WALL_AT_2)
{
    /* Clear the walls from previous test */
    MAPPGridState::walls.clear();

    /* Load some agents */
    vector<Agent> agents;
    agents.push_back(agent_1);

    MAPPGridState::walls.push_back(Wall(0,0));
    MAPPGridState grid( agents, 10, 10,0 );

    EXPECT_EQ( grid.hasWallAt(0,0), true);
    EXPECT_EQ( grid.hasWallAt(0,1), false);
}

TEST_F(AstarTests, SUCC_COORDS_1)
{
    vector<Agent> agents;
    agents.push_back(agent_1);

    MAPPGridState grid( agents, 10, 10, 5 );

    agents.clear();
    grid.succCoords(agents, agent_1);

    vector<Agent> succAgents;
    succAgents.push_back(agent_1);
    succAgents.push_back(agent_1);
    succAgents.at(0).setX( succAgents.at(0).getX() + 1 );
    succAgents.at(1).setY( succAgents.at(1).getY() + 1);

    ASSERT_EQ( succAgents , agents );
}

TEST_F(AstarTests, SUCC_COORDS_2)
{
    vector<Agent> agents;
    agents.push_back(agent_4);

    MAPPGridState grid( agents, 10, 10, 5 );

    agents.clear();
    grid.succCoords(agents, agent_4);

    vector<Agent> succAgents;
    succAgents.push_back(agent_4);
    succAgents.push_back(agent_4);
    succAgents.push_back(agent_4);
    succAgents.push_back(agent_4);

    succAgents.at(0).setX( succAgents.at(0).getX() + 1 );
    succAgents.at(1).setX( succAgents.at(1).getX() - 1);
    succAgents.at(2).setY( succAgents.at(2).getY() + 1);
    succAgents.at(3).setY( succAgents.at(3).getY() - 1);


    EXPECT_EQ( succAgents , agents );
    
}

TEST_F(AstarTests, SAME_COORD)
{
    vector<Agent> agents;
    agents.push_back(agent_1);

    MAPPGridState grid( agents, 10, 10, 5 );
    EXPECT_EQ(grid.sameCoord(agent_1, agent_6), true);
    EXPECT_EQ(grid.sameCoord(agent_1, agent_5), false);

}

TEST_F(AstarTests, GOOD_SUCCESSOR)
{
    /*
    * Good successor only compares the coordinates of the agents 
    * in the successor state, it only matters that the size of the grid.agents
    * and successors are the same.
    */  
    vector<Agent> agents;
    vector<Agent> successors;
    agents.push_back(agent_1);
    agents.push_back(agent_2);
    agents.push_back(agent_3);

    MAPPGridState grid( agents, 10, 10, 5 );

    successors.push_back(agent_1);
    successors.push_back(agent_2);
    successors.push_back(agent_1);
    EXPECT_EQ( grid.goodSuccessor(successors), false);

    successors.clear();
    successors.push_back(agent_1);
    successors.push_back(agent_2);
    successors.push_back(agent_3);
    EXPECT_EQ( grid.goodSuccessor(successors), true );

    successors.clear();
    successors.push_back(agent_1);
    successors.push_back(agent_1);
    successors.push_back(agent_2);
    EXPECT_EQ( grid.goodSuccessor(successors), false );

    successors.clear();
    successors.push_back(agent_1);
    successors.push_back(agent_2);
    successors.push_back(agent_2);
    EXPECT_EQ( grid.goodSuccessor(successors), false);

    ASSERT_NO_THROW( grid.goodSuccessor(successors) );

    /* If the successor has more agents than the current state, expect exception */
    successors.push_back(agent_3);
    ASSERT_ANY_THROW( grid.goodSuccessor(successors) );
}

TEST_F(AstarTests, SUCCESSORS)
{
    /**
     * !IMPLEMENT THIS!
     */ 
}