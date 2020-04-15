#include "../Astar.cpp"

#include<gtest/gtest.h>

struct AstarTests: public ::testing::Test
{
    /* Create some agents for the test */
    Agent agent_1 = Agent(0,0, 10,10,"Agent 1");
    Agent agent_2 = Agent(0,1, 7,5,"Agent 2");
    Agent agent_3 = Agent(4,3, 3,4,"Agent 3");
    Agent agent_4 = Agent(5,5, 1,1,"Agent 4");
    Agent agent_5 = Agent(6,6, 10,10,"Agent 5");
    
};

/* Test the hasWallAt static method */
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