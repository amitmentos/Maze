#pragma once
#include <iostream>
#include <vector>
#include "maze.hpp"
#include "cell.hpp"
// #include "algorithm.hpp"
using namespace std;

class MazeSolution
{
private:
    Maze maze;
    // Algorithm *algorithms;
    vector<Cell> path;

public:
    MazeSolution();
    // MazeSolution(const Maze &m, Algorithm *alg);

    void display();

    // Algorithm *getAlgorithm() const{return algorithms;}
    Maze& getMaze() {return maze;}
    vector<Cell> getPath() const{return path;}
};