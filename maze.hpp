#pragma once
#include <iostream>
#include <string.h>
#include "point.hpp"
#include "cell.hpp"
#include <vector>
using namespace std;


class Maze {
private:
    int size;
    string mazeName;
    Cell** mazeBoard;
    Cell* startPoint;
    Cell* endPoint;
    Cell* userPoint;

public:
    Maze(){};
    Maze(int size, const string& name);
    Maze(const Maze& toCopy);
    ~Maze();
    void display() ;
    int getSize() const { return size; }
    string getMazeName() const { return mazeName; }
    Cell** getBoard() const { return mazeBoard; }
    Cell* getStartPoint() const { return startPoint; }
    Cell* getEndPoint() const { return endPoint; }
    Cell* getCell(int i, int j)const{return &mazeBoard[i][j];}
    Cell* getUserPoint()const{return userPoint;}
    void setCell(int x, int y, int cellValue);
    void setUserPoint(int x,int y){this->getUserPoint()->setX(x); this->getUserPoint()->setY(y);}
    vector<Cell*> getNeighbors  (const Maze &maze, Cell *cell)const;
};

class noMazeFound:public Maze{

};