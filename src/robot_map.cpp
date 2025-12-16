#include "robot_map.h"
#include <stdexcept>

RobotMap::RobotMap() : size(0), robotPosition({0, 0}) {
}

RobotMap::~RobotMap() {
}

void RobotMap::setDimension(int n) {
    if (n <= 0) {
        throw std::invalid_argument("Dimension must be a positive integer.");
    }
    size = n;
    grid.assign(size, std::vector<bool>(size, false));
    robotPosition = {0, 0}; // Reset position to origin
}

bool RobotMap::isWithinBounds(Coordinate pos) {
    return pos.x >= 0 && pos.x < size && pos.y >= 0 && pos.y < size;
}

void RobotMap::moveTo(Coordinate newPosition) {
    if (!isWithinBounds(newPosition)) {
        throw std::out_of_range("Move target out of bounds.");
    }
    robotPosition = newPosition;
}

void RobotMap::lineTo(Coordinate targetPosition) {
    if (!isWithinBounds(targetPosition)) {
        throw std::out_of_range("Line target out of bounds.");
    }

    int x0 = robotPosition.x;
    int y0 = robotPosition.y;
    int x1 = targetPosition.x;
    int y1 = targetPosition.y;

    int dx = std::abs(x1 - x0);
    int dy = std::abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx - dy;

    while (true) {
        grid[y0][x0] = true; // Mark cell

        if (x0 == x1 && y0 == y1) break;

        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x0 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y0 += sy;
        }
    }

    robotPosition = targetPosition;
}

void RobotMap::printMap() {
    for (int y = 0; y < size; ++y) {
        for (int x = 0; x < size; ++x) {
            std::cout << (grid[y][x] ? "+ " : ". ");
        }
        std::cout << "\n";
    }
}

int RobotMap::getSize() const {
    return size;
}
