#pragma once
#include <vector>
#include <string>
#include "cell.hpp"
#include "mazeSolution.hpp"
using namespace std;

namespace std {
    template <>
    struct hash<Point> {
        size_t operator()(const Point& p) const {
            // Use a simple hash combining the x and y values
            size_t h1 = std::hash<int>{}(p.getX());
            size_t h2 = std::hash<int>{}(p.getY());
            return h1 ^ (h2 << 1);
        }
    };
}


class Algorithm: public MazeSolution {
    protected:
        string algorithmName;
    public:
        string getAlgorithmName(){return algorithmName;};
        virtual vector<Cell> solveMaze(const Maze& maze) = 0;
};

class AlgorithmList {
protected:
    vector<Algorithm*> algorithms;
    Algorithm* currentAlgorithm;

public:
    AlgorithmList():currentAlgorithm(nullptr){};
    void addAlgorithm(Algorithm* newAlgorithm){algorithms.push_back(newAlgorithm);};
    void changeAlgorithm(const string& name);
    Algorithm* getAlgorithm(const string& name);
};

// class prim : public Algorithm {
// public: 
//     vector<Cell> solveMaze(const Maze& maze) override;
// };

// class AStar : public Algorithm {
// public:
//     vector<Cell> solveMaze(const Maze& maze) override;
// };

class DFS : public Algorithm {
public:
    vector<Cell> solveMaze(const Maze& maze) override;
};


class BFS: public Algorithm{
    public:
    vector<Cell> solveMaze(const Maze& maze) override;
};