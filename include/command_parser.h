#ifndef COMMAND_PARSER_H
#define COMMAND_PARSER_H

#include <vector>
#include <memory>
#include <string>
#include <iostream>
#include "command.h"

class CommandParser {
public:
    std::vector<std::unique_ptr<Command>> parseCommands(std::istream& input);
private:
    std::string sanitizeLine(std::string line);
};

#endif // COMMAND_PARSER_H
