#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <memory>
#include <algorithm>
#include "robot_map.h"
#include "command.h"

std::string sanitizeLine(std::string line) {
    std::replace(line.begin(), line.end(), ',', ' ');
    return line;
}

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

    RobotMap robotMap;
    std::string line;
    int lineNum = 0;

    while (std::getline(file, line)) {
        lineNum++;
        
        if (line.empty()) continue;

        std::string sanitized = sanitizeLine(line);
        std::stringstream ss(sanitized);
        std::string cmdType;
        ss >> cmdType;

        if (cmdType.empty()) continue;

        try {
            std::unique_ptr<Command> command;

            if (cmdType == "DIMENSION") {
                int n;
                if (!(ss >> n)) throw std::runtime_error("Invalid arguments for DIMENSION");
                command = std::unique_ptr<Command>(new DimensionCommand(n));
            } else if (cmdType == "MOVE_TO") {
                int x, y;
                if (!(ss >> x >> y)) throw std::runtime_error("Invalid arguments for MOVE_TO");
                command = std::unique_ptr<Command>(new MoveToCommand(x, y));
            } else if (cmdType == "LINE_TO") {
                int x, y;
                if (!(ss >> x >> y)) throw std::runtime_error("Invalid arguments for LINE_TO");
                command = std::unique_ptr<Command>(new LineToCommand(x, y));
            } else {
                std::cerr << "Warning: Unknown command '" << cmdType << "' at line " << lineNum << std::endl;
                continue;
            }

            if (command) {
                command->execute(robotMap);
            }
        } catch (const std::exception& e) {
            std::cerr << "Error at line " << lineNum << ": " << e.what() << " Skip this line" << std::endl;
        }
    }

    robotMap.printMap();

    return 0;
}
