#include <iostream>
#include <fstream>
#include "robot_map.h"
#include "command_parser.h"

int main(int argc, char* argv[]) {
    std::string filename = "commands.txt";
    if (argc > 1) {
        filename = argv[1];
    }

    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return 1;
    }

    CommandParser parser;
    auto commands = parser.parseCommands(file);

    RobotMap robotMap;
    for (const auto& cmd : commands) {
        try {
            cmd->execute(robotMap);
        } catch (const std::exception& e) {
             std::cerr << "Runtime Error: " << e.what() << std::endl;
        }
    }

    robotMap.printMap();

    return 0;
}
