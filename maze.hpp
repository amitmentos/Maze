#pragma once
#include <iostream>
#include <string.h>
#include "point.hpp"

using namespace std;


class Maze {
private:
    int size;
    string mazeName;
    int** mazeBoard;
    Point startPoint;
    Point endPoint;

public:
    Maze();
    Maze(int size, const string& name);
    ~Maze();
    void display() const;
    int getSize() const { return size; }
    string getMazeName() const { return mazeName; }
    int** getBoard() const { return mazeBoard; }
    Point getStartPoint() const { return startPoint; }
    Point getEndPoint() const { return endPoint; }
};

