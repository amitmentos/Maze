#pragma once
#include <iostream>
using namespace std; 
#include "maze.hpp"

class Maze2dGenerator: public Maze {
public:
    virtual ~Maze2dGenerator() {}
    virtual void generate() = 0;
    virtual void compress() = 0;
    float measureAlgorithmTime(); 
};

class SimpleMaze2dGenerator : public Maze2dGenerator {
public:
    SimpleMaze2dGenerator() {}
    ~SimpleMaze2dGenerator() {}
    virtual void compress();
    virtual void generate();
};