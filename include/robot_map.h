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
    int getSize() const;

private:
    int size;
    std::vector<std::vector<bool>> grid;
    Coordinate robotPosition;
    
    bool isWithinBounds(Coordinate pos);
};

#endif // ROBOT_MAP_H