#pragma once
#include "point.hpp"

class Cell : public Point
{
private:
    Point cellPoint;
    bool cellType;

public:
    Cell(const Point &point, bool type) : cellPoint(point), cellType(type) {}
    Cell(int x, int y, bool type) : Point(x, y), cellType(type) {}
    Cell() : cellType(true){};
    Point getPoint() const { return cellPoint; }
    bool isWalkable() const { return cellType; }
    bool getType() { return cellType; }
    bool getType() const { return cellType; }
    void setType(int toSet) { cellType = toSet; }
    void operator=(const Cell &toInsert)
    {
        cellPoint.setX(toInsert.getX());
        cellPoint.setY(toInsert.getY());
        cellType = toInsert.getType();
    }
    bool operator==(const Cell &other) const
    {
        return this->x == other.x && this->y == other.y && this->cellType == other.cellType;
    }
};