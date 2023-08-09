#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "maze.hpp"
#include "mazeSolution.hpp"
using namespace std; 



class Maze2dGenerator{
public:
    virtual ~Maze2dGenerator() {}
    virtual Maze generate(int size,string) = 0;
};

class SimpleMaze2dGenerator : public Maze2dGenerator {
public:
    SimpleMaze2dGenerator() {}
    ~SimpleMaze2dGenerator() {}
    virtual Maze generate(int size,string);
    bool hasSolution(const Maze &maze);
    Maze generateNewMaze(int size, string mazeName);
};

class MazeCompressor {
public:
    vector<string> compress(const Maze& maze);
    Maze decompress(const string& fileName, int index);
    MazeSolution decompressPath(const std::string& mazeName);
    bool writeStringToFile(const vector<string>& content);
    bool writePathToFile(const MazeSolution& content);
    bool appendContentToFile(const vector<string>& content, int fileIndex);
};



class myMaze2dGenerator : public Maze2dGenerator {
public:
    myMaze2dGenerator() {}
    ~myMaze2dGenerator() {}
    virtual Maze generate(int size,string);

};

