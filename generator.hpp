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
    // virtual void compress(Maze& maze) = 0;
    // virtual float measureAlgorithmTime(int size, string mazeName)=0; 
};

class SimpleMaze2dGenerator : public Maze2dGenerator {
public:
    SimpleMaze2dGenerator() {}
    ~SimpleMaze2dGenerator() {}
    // virtual void compress(Maze& maze);
    virtual Maze generate(int size,string);
    bool hasSolution(const Maze &maze);
    // virtual float measureAlgorithmTime(int size, string mazeName); 
};
class MazeCompressor {
public:
    vector<string> compress(const Maze& maze);
    Maze decompress(const string& compressedData);
};



// #pragma once
// #include <iostream>
// using namespace std; 
// #include "maze.hpp"


// class Maze2dGenerator{
// public:
//     virtual ~Maze2dGenerator() {}
//     virtual Maze generate(int size,string) = 0;
//     virtual void compress(Maze& maze) = 0;
//     // virtual float measureAlgorithmTime(int size, string mazeName)=0; 
// };

// class SimpleMaze2dGenerator : public Maze2dGenerator {
// public:
//     SimpleMaze2dGenerator() {}
//     ~SimpleMaze2dGenerator() {}
//     virtual void compress(Maze& maze);
//     virtual Maze generate(int size,string);
//     bool hasSolution(const Maze &maze);
//     // virtual float measureAlgorithmTime(int size, string mazeName); 
// };