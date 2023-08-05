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
    string name;
    // Algorithm *algorithms;
    vector<Cell> path;

public:
    MazeSolution();
    // MazeSolution(const Maze &m, Algorithm *alg);

    void display();

    // Algorithm *getAlgorithm() const{return algorithms;}
    string getMazeName() {return name;}
    vector<Cell> getPath() const{return path;}
    void setPath(const vector<Cell>& toSet){path=toSet;}
    void setName(const string& toCopy){name = toCopy;}
};