#include <gtest/gtest.h>
#include "robot_map.h"

class RobotMapTest : public ::testing::Test {
protected:
    RobotMap robotMap;

    void SetUp() override {
        robotMap.setDimension(5);
    }
};

TEST_F(RobotMapTest, InitialState) {
    EXPECT_EQ(robotMap.getSize(), 5);
    Coordinate pos = robotMap.getPosition();
    EXPECT_EQ(pos.x, 0);
    EXPECT_EQ(pos.y, 0);
}

TEST_F(RobotMapTest, MoveToValid) {
    robotMap.moveTo({2, 3});
    Coordinate pos = robotMap.getPosition();
    EXPECT_EQ(pos.x, 2);
    EXPECT_EQ(pos.y, 3);
}

TEST_F(RobotMapTest, MoveToOutOfBounds) {
    EXPECT_THROW(robotMap.moveTo({-1, 0}), std::out_of_range);
    EXPECT_THROW(robotMap.moveTo({5, 0}), std::out_of_range);
    EXPECT_THROW(robotMap.moveTo({0, 5}), std::out_of_range);
}

TEST_F(RobotMapTest, LineToValid) {
    robotMap.lineTo({2, 2});
    EXPECT_TRUE(robotMap.isMarked(0, 0));
    EXPECT_TRUE(robotMap.isMarked(1, 1));
    EXPECT_TRUE(robotMap.isMarked(2, 2));
    EXPECT_FALSE(robotMap.isMarked(0, 1));
}

TEST_F(RobotMapTest, LineToOutOfBounds) {
    EXPECT_THROW(robotMap.lineTo({5, 5}), std::out_of_range);
}

TEST_F(RobotMapTest, LineToDiagonal) {
    robotMap.lineTo({4, 4});
    for (int i = 0; i <= 4; ++i) {
        EXPECT_TRUE(robotMap.isMarked(i, i));
    }
}

TEST_F(RobotMapTest, LineToHorizontal) {
    robotMap.lineTo({4, 0});
    for (int x = 0; x <= 4; ++x) {
        EXPECT_TRUE(robotMap.isMarked(x, 0));
    }
}

TEST_F(RobotMapTest, LineToVertical) {
    robotMap.lineTo({0, 4});
    for (int y = 0; y <= 4; ++y) {
        EXPECT_TRUE(robotMap.isMarked(0, y));
    }
}
