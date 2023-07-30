#pragma once
class Point {
    protected:
        int x;
        int y;

    public:
        Point(int x = 0, int y = 0) : x(x), y(y) {}

        int getX() const { return x; }
        int getY() const { return y; }

        void setX(int newX) { x = newX; }
        void setY(int newY) { y = newY; }
};