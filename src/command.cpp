#include "command.h"

DimensionCommand::DimensionCommand(int n) : n(n) {}
void DimensionCommand::execute(RobotMap& robotMap) {
    robotMap.setDimension(n);
}

MoveToCommand::MoveToCommand(int x, int y) : target({x, y}) {}
void MoveToCommand::execute(RobotMap& robotMap) {
    robotMap.moveTo(target);
}

LineToCommand::LineToCommand(int x, int y) : target({x, y}) {}
void LineToCommand::execute(RobotMap& robotMap) {
    robotMap.lineTo(target);
}
