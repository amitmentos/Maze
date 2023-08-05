// #pragma once
// #include <vector>
// #include <string>
// #include "cell.hpp"
// #include "mazeSolution.hpp"
// using namespace std;

// namespace std {
//     template <>
//     struct hash<Point> {
//         size_t operator()(const Point& p) const {
//             // Use a simple hash combining the x and y values
//             size_t h1 = std::hash<int>{}(p.getX());
//             size_t h2 = std::hash<int>{}(p.getY());
//             return h1 ^ (h2 << 1);
//         }
//     };
// }


// class Algorithm: public MazeSolution {
//     protected:
//         string algorithmName;
//     public:
//         string getAlgorithmName(){return algorithmName;};
//         virtual vector<Cell> solveMaze(const Maze& maze) = 0;
// };

// class AlgorithmList {
// protected:
//     vector<Algorithm*> algorithms;
//     Algorithm* currentAlgorithm;

// public:
//     AlgorithmList():currentAlgorithm(nullptr){};
//     void addAlgorithm(Algorithm* newAlgorithm){algorithms.push_back(newAlgorithm);};
//     void changeAlgorithm(const string& name);
//     Algorithm* getAlgorithm(const string& name);
// };

// class DFS : public Algorithm {
// public:
//     vector<Cell> solveMaze(const Maze& maze) override;
// };


// class BFS : public Algorithm {
// public:
//     vector<Cell> solveMaze(const Maze& maze) override;

// private:
//     struct Node {
//         Cell cell;
//         vector<Cell> path;

//         Node(const Cell& c, const vector<Cell>& p) : cell(c), path(p) {}
//     };
// };


#pragma once
#include <vector>
#include <string>
#include "cell.hpp"
#include "mazeSolution.hpp"
#include <queue>
#include <cmath>
#include <map>
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

class AStar : public Algorithm {
private:
    struct Node {
        Cell *cell;
        Node *parent;
        float g; // cost from start to this node
        float h; // heuristic cost from this node to goal
        float f; // total cost

        Node(Cell *cell, Node *parent, float g, float h) : cell(cell), parent(parent), g(g), h(h), f(g+h) {}
    };

    struct CompareNode {
        bool operator()(const Node *a, const Node *b) const {
            return a->f > b->f;
        }
    };

    float heuristic(const Cell &start, const Cell &goal) {
        return abs(start.getX() - goal.getX()) + abs(start.getY() - goal.getY());
    }

public:
    std::vector<Cell> solveMaze(const Maze &maze);
};

class DFS : public Algorithm {
public:
    vector<Cell> solveMaze(const Maze& maze) override;
};


class BFS : public Algorithm {
public:
    vector<Cell> solveMaze(const Maze& maze) override;

private:
    struct Node {
        Cell cell;
        vector<Cell> path;

        Node(const Cell& c, const vector<Cell>& p) : cell(c), path(p) {}
    };
};

class Prim: public Algorithm {
public:
    vector<Cell> solveMaze(const Maze& maze) override;
};