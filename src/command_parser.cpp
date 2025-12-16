#include "command_parser.h"
#include <sstream>
#include <algorithm>
#include <stdexcept>

std::string CommandParser::sanitizeLine(std::string line) {
    std::replace(line.begin(), line.end(), ',', ' ');
    return line;
}

std::vector<std::unique_ptr<Command>> CommandParser::parseCommands(std::istream& input) {
    std::vector<std::unique_ptr<Command>> commands;
    std::string line;
    int lineNum = 0;

    while (std::getline(input, line)) {
        lineNum++;
        if (line.empty()) continue;

        std::string sanitized = sanitizeLine(line);
        std::stringstream ss(sanitized);
        std::string cmdType;
        ss >> cmdType;

        if (cmdType.empty()) continue;

        try {
            if (cmdType == "DIMENSION") {
                int n;
                if (!(ss >> n)) throw std::runtime_error("Invalid arguments for DIMENSION");
                commands.push_back(std::unique_ptr<Command>(new DimensionCommand(n)));
            } else if (cmdType == "MOVE_TO") {
                int x, y;
                if (!(ss >> x >> y)) throw std::runtime_error("Invalid arguments for MOVE_TO");
                commands.push_back(std::unique_ptr<Command>(new MoveToCommand(x, y)));
            } else if (cmdType == "LINE_TO") {
                int x, y;
                if (!(ss >> x >> y)) throw std::runtime_error("Invalid arguments for LINE_TO");
                commands.push_back(std::unique_ptr<Command>(new LineToCommand(x, y)));
            } else {
                std::cerr << "Warning: Unknown command '" << cmdType << "' at line " << lineNum << std::endl;
            }
        } catch (const std::exception& e) {
            std::cerr << "Error at line " << lineNum << ": " << e.what() << " Skip this line" << std::endl;
        }
    }
    return commands;
}
