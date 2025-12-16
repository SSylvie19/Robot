#include <gtest/gtest.h>
#include "command_parser.h"
#include <sstream>

class CommandParserTest : public ::testing::Test {
protected:
    CommandParser parser;
};

TEST_F(CommandParserTest, ParseValidCommands) {
    std::string input = "DIMENSION 5\nMOVE_TO 1,1\nLINE_TO 2,2";
    std::stringstream ss(input);
    auto commands = parser.parseCommands(ss);

    ASSERT_EQ(commands.size(), 3);

    RobotMap map;
    commands[0]->execute(map);
    EXPECT_EQ(map.getSize(), 5);

    commands[1]->execute(map);
    Coordinate pos = map.getPosition();
    EXPECT_EQ(pos.x, 1);
    EXPECT_EQ(pos.y, 1);

    commands[2]->execute(map);
    EXPECT_TRUE(map.isMarked(2, 2));
}

TEST_F(CommandParserTest, ParseInvalidCommands) {
    std::string input = "INVALID_CMD\nDIMENSION 5";
    std::stringstream ss(input);
    auto commands = parser.parseCommands(ss);

    ASSERT_EQ(commands.size(), 1);
}

TEST_F(CommandParserTest, ParseEmptyLines) {
    std::string input = "\n\nDIMENSION 5\n\n";
    std::stringstream ss(input);
    auto commands = parser.parseCommands(ss);

    ASSERT_EQ(commands.size(), 1);
}

TEST_F(CommandParserTest, ParseMalformedArgs) {
    std::string input = "DIMENSION abc\nMOVE_TO 1";
    std::stringstream ss(input);
    auto commands = parser.parseCommands(ss);

    ASSERT_EQ(commands.size(), 0);
}
