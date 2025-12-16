#ifndef COMMAND_H
#define COMMAND_H

#include "robot_map.h"
#include "type.h"
#include <memory>

class Command {
public:
    virtual ~Command() = default;
    virtual void execute(RobotMap& robotMap) = 0;
};

class DimensionCommand : public Command {
    int n;
public:
    DimensionCommand(int n);
    void execute(RobotMap& robotMap) override;
};

class MoveToCommand : public Command {
    Coordinate target;
public:
    MoveToCommand(int x, int y);
    void execute(RobotMap& robotMap) override;
};

class LineToCommand : public Command {
    Coordinate target;
public:
    LineToCommand(int x, int y);
    void execute(RobotMap& robotMap) override;
};

#endif // COMMAND_H
