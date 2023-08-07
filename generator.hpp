#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "maze.hpp"
using namespace std; 



class Maze2dGenerator{
public:
    virtual ~Maze2dGenerator() {}
    virtual Maze generate(int size,string) = 0;
    // virtual float measureAlgorithmTime(Maze& maze)=0; 
};

class SimpleMaze2dGenerator : public Maze2dGenerator {
public:
    SimpleMaze2dGenerator() {}
    ~SimpleMaze2dGenerator() {}
    // virtual void compress(Maze& maze);
    virtual Maze generate(int size,string);
    bool hasSolution(const Maze &maze);
    Maze generateNewMaze(int size, string mazeName);
    // virtual float measureAlgorithmTime(Maze& maze); 
};

class MazeCompressor {
public:
    vector<string> compress(const Maze& maze);
    Maze decompress(int index);
    bool writeStringToFile(const vector<string>& content);
    bool appendContentToFile(const vector<string>& content, int fileIndex);
};



class myMaze2dGenerator : public Maze2dGenerator {
public:
    myMaze2dGenerator() {}
    ~myMaze2dGenerator() {}
    // virtual void compress(Maze& maze);
    virtual Maze generate(int size,string);

};

