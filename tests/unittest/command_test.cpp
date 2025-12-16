#include <gtest/gtest.h>
#include "command.h"
#include "robot_map.h"

class CommandTest : public ::testing::Test {
protected:
    RobotMap robotMap;
};

TEST_F(CommandTest, DimensionCommand) {
    DimensionCommand cmd(10);
    cmd.execute(robotMap);
    EXPECT_EQ(robotMap.getSize(), 10);
}

TEST_F(CommandTest, MoveToCommand) {
    robotMap.setDimension(5);
    MoveToCommand cmd(3, 3);
    cmd.execute(robotMap);
    Coordinate pos = robotMap.getPosition();
    EXPECT_EQ(pos.x, 3);
    EXPECT_EQ(pos.y, 3);
}

TEST_F(CommandTest, LineToCommand) {
    robotMap.setDimension(5);
    LineToCommand cmd(2, 2);
    cmd.execute(robotMap);
    EXPECT_TRUE(robotMap.isMarked(0, 0));
    EXPECT_TRUE(robotMap.isMarked(1, 1));
    EXPECT_TRUE(robotMap.isMarked(2, 2));
}
