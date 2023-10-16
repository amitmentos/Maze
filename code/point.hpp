#pragma once

class Point {
protected:
    int x;
    int y;
    Point* parent;

public:
    Point(int _x = 0, int _y = 0, Point* _parent = nullptr) : x(_x), y(_y), parent(_parent) {}

    int getX() const { return x; }
    int getY() const { return y; }
    Point* getParent() const { return parent; }

    void setX(int newX) { x = newX; }
    void setY(int newY) { y = newY; }
    void setParent(Point* newParent) { parent = newParent; }

    bool operator==(const Point& other) const {
        return x == other.x && y == other.y;
    }

    bool operator!=(const Point& other) const {
        return !(*this == other);
    }
};
