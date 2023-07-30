#pragma once
#include <vector>
#include <string>
#include "cell.hpp"
#include "mazeSolution.hpp"
using namespace std;

class Algorithm : public MazeSolution {
protected:
    Algorithm* algorithms;
    Algorithm* currentAlgorithm;

public:
    Algorithm();
    void addAlgorithm(Algorithm* newAlgorithm);
    Algorithm* getAlgorithm(const string& name);
    virtual vector<Cell> solveMaze(const Maze& maze) = 0;
    void changeAlgorithm(const string& name);
};

class prim : public Algorithm {
public: 
    vector<Cell> solveMaze(const Maze& maze) override;
};

class AStar : public Algorithm {
public:
    vector<Cell> solveMaze(const Maze& maze) override;
};

class DFS : public Algorithm {
public:
    vector<Cell> solveMaze(const Maze& maze) override;
};

