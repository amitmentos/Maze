#pragma once
#include "point.hpp"

class Cell:public Point {
private:
    Point cellPoint;
    bool cellType;

public:
    Cell(const Point& point, bool type) : cellPoint(point), cellType(type) {}
    Point getPoint() const { return cellPoint; }
    bool isWalkable() const { return cellType; }
};