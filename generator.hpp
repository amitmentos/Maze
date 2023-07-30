#pragma once
#include <iostream>
using namespace std; 
#include "maze.hpp"
#include "algorithm.hpp"


class Maze2dGenerator: public Maze {
public:
    virtual ~Maze2dGenerator() {}
    virtual Maze generate(int size) = 0;
    virtual void compress() = 0;
    float measureAlgorithmTime(); 
};

class SimpleMaze2dGenerator : public Maze2dGenerator {
public:
    SimpleMaze2dGenerator() {}
    ~SimpleMaze2dGenerator() {}
    virtual void compress();
    virtual Maze generate(int size);
};
class RandomMaze2dGenerator : public Maze2dGenerator {
public:
    RandomMaze2dGenerator() {}
    ~RandomMaze2dGenerator() {}
    virtual void compress() override; // Overriding as virtual in base class.
    virtual Maze generate(int size) override;
    bool hasSolution(const Maze& maze);
};