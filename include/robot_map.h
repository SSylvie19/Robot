#ifndef ROBOT_MAP_H
#define ROBOT_MAP_H

#include <vector>
#include <iostream>
#include <cmath>
#include <algorithm>
#include "type.h"

class RobotMap {
public:
    RobotMap();
    ~RobotMap();
    void setDimension(int n);
    void moveTo(Coordinate newPosition);
    void lineTo(Coordinate targetPosition);
    void printMap();
    int getSize();
    bool isMarked(int x, int y);
    Coordinate getPosition();

private:
    int size;
    std::vector<std::vector<bool>> grid;
    Coordinate robotPosition;

    bool isWithinBounds(Coordinate pos) const;
};

#endif // ROBOT_MAP_H