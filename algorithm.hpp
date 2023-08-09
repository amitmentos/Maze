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
        virtual ostream& getAlgorithmNameOS(ostream &os) = 0;
};

class AlgorithmList {
protected:
    vector<Algorithm*> algorithms;

public:
    AlgorithmList(){};
    void addAlgorithm(Algorithm* newAlgorithm){algorithms.push_back(newAlgorithm);};
    Algorithm* getAlgorithm(const int index){return algorithms[index];}
    Algorithm* getAlgorithm(const string &name);
};


class AStar : public Algorithm {
private:
    struct Node {
        Cell *cell;
        Node *parent;
        float g; 
        float h;
        float f; 

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
    vector<Cell> solveMaze(const Maze &maze);
    ostream& getAlgorithmNameOS(ostream &os) override {return os << "A*";}
};



class DFS : public Algorithm {
public:
    vector<Cell> solveMaze(const Maze& maze) override;
    ostream& getAlgorithmNameOS(ostream &os) override {return os << "DFS";}
};


class BFS : public Algorithm {
public:
    vector<Cell> solveMaze(const Maze& maze) override;
    ostream& getAlgorithmNameOS(ostream &os) override {return os << "BFS";}

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
    ostream& getAlgorithmNameOS(ostream &os) override {return os << "Prim";}
};