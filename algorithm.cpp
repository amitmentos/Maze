#include "algorithm.hpp"
#include <unordered_map>
#include "cell.hpp"
#include "point.hpp"
#include <string.h>
#include <iostream>
#include <cstdlib>
#include <stack>
#include <algorithm>
#include <queue>
#include <cmath>
using namespace std;

// Algorithm::Algorithm() :algorithmName(nullptr) {}

Algorithm* AlgorithmList::getAlgorithm(const std::string& name) {
    for (Algorithm* algorithm : algorithms) {
        if (algorithm->getAlgorithmName()== name)
            return algorithm;
    }
    return nullptr;
}

void AlgorithmList::changeAlgorithm(const std::string& name) {
    currentAlgorithm = getAlgorithm(name);
}

vector<Cell> DFS::solveMaze(const Maze& maze) {
       
    int mazeSize = maze.getSize();
    Cell** mazeBoard = maze.getBoard();
    
    Cell* start = maze.getStartPoint();
    Cell* end = maze.getEndPoint();
    
    // Use a matrix to keep track of visited cells
    vector<vector<bool>> visited(mazeSize, vector<bool>(mazeSize, false));
    
    // Use a stack for DFS
    stack<Cell*> s;
    s.push(start);
    
    // We can also use a matrix to remember the parent of each cell
    vector<vector<Cell*>> parent(mazeSize, vector<Cell*>(mazeSize, nullptr));
    
    vector<int> dx = {0, 1, 0, -1};
    vector<int> dy = {1, 0, -1, 0};
    
    visited[start->getPoint().getX()][start->getPoint().getY()] = true;

    while(!s.empty()) {
        Cell* curr = s.top();
        s.pop();
        
        // If we reach the end point, we stop
        if(curr == end) {
            vector<Cell> path;
            while(curr != start) {
                path.push_back(*curr);
                curr = parent[curr->getPoint().getX()][curr->getPoint().getY()];
            }
            path.push_back(*start);
            reverse(path.begin(), path.end());
            return path;
        }
        
        for(int i = 0; i < 4; i++) {
            int newX = curr->getPoint().getX() + dx[i];
            int newY = curr->getPoint().getY() + dy[i];
            
            // Check boundaries
            if(newX >= 0 && newX < mazeSize && newY >= 0 && newY < mazeSize) {
                if(!visited[newX][newY] && mazeBoard[newX][newY].isWalkable()) {
                    s.push(&mazeBoard[newX][newY]);
                    visited[newX][newY] = true;
                    parent[newX][newY] = curr;
                }
            }
        }
    }

    // Return an empty vector if there is no solution
    return vector<Cell>();
}



std::vector<Cell> BFS::solveMaze(const Maze& maze) {
    int size = maze.getSize();

    // Create a 2D vector to keep track of visited cells
    std::vector<std::vector<bool>> visited(size, std::vector<bool>(size, false));

    // Create a queue to perform BFS
    std::queue<Point> q;

    // Get the start point from the maze
    Point startPoint = *maze.getStartPoint();

    // Enqueue the start point and mark it as visited
    q.push(startPoint);
    visited[startPoint.getX()][startPoint.getY()] = true;

    // Map to keep track of the parent cell to reconstruct the path later
    unordered_map<Point, Point> parent;

    // Perform BFS
    while (!q.empty()) {
        Point current = q.front();
        q.pop();

        // Get the neighbors of the current cell
        std::vector<Point> neighbors = {
            Point(current.getX() + 1, current.getY(), nullptr),
            Point(current.getX() - 1, current.getY(), nullptr),
            Point(current.getX(), current.getY() + 1, nullptr),
            Point(current.getX(), current.getY() - 1, nullptr)
        };

        // Visit the unvisited neighbors and add them to the queue
        for (const Point& neighbor : neighbors) {
            int x = neighbor.getX();
            int y = neighbor.getY();

            if (x >= 0 && x < size && y >= 0 && y < size && !visited[x][y] && maze.getCell(x, y)->getType() == true) {
                q.push(neighbor);
                visited[x][y] = true;
                parent[neighbor] = current;
            }
        }
    }

    // Reconstruct the path and return a vector of Cell objects representing the path
    std::vector<Cell> path;
    Point currentPoint = startPoint;

    if (parent.find(currentPoint) != parent.end()) {
        while (parent.find(currentPoint) != parent.end()) {
            path.push_back(Cell(currentPoint.getX(), currentPoint.getY(), true));
            currentPoint = parent[currentPoint];
        }

        // Add the start point to the path
        path.push_back(Cell(startPoint.getX(), startPoint.getY(), true));

        // Reverse the path so that it starts from the start point and ends at the end point
        std::reverse(path.begin(), path.end());
    }

    return path;
}



// vector<Cell> AStar::solveMaze(const Maze& maze) {
//     struct Node {
//         Cell cell;
//         Node* parent;
//         double g, h, f;
//     };
    
//     auto computeH = [](const Point& a, const Point& b) -> double {
//         return sqrt((a.getX() - b.getX()) * (a.getX() - b.getX()) + (a.getY() - b.getY()) * (a.getY() - b.getY()));
//     };

//     vector<Node*> openList;
//     vector<Node*> closedList;

//     Node* start = new Node{maze.getStartPoint(), nullptr, 0, computeH(maze.getStartPoint().getPoint(), maze.getEndPoint().getPoint()), computeH(maze.getStartPoint().getPoint(), maze.getEndPoint().getPoint())};
//     Node* goal = nullptr;

//     openList.push_back(start);

//     while(!openList.empty()) {
//         Node* current = min_element(openList.begin(), openList.end(), [](Node a, Node* b) {
//             return a->f < b->f;
//         });

//         if(current->cell.getPoint().getX() == maze.getEndPoint()->getPoint().getX() && current->cell.getPoint().getY() == maze.getEndPoint().getPoint().getY()) {
//             goal = current;
//             break;
//         }

//         openList.erase(remove(openList.begin(), openList.end(), current), openList.end());
//         closedList.push_back(current);

//         // Generate successors (for simplicity, we assume 4-connected grid: up, down, left, right)
//         for(int dx = -1; dx <= 1; dx++) {
//             for(int dy = -1; dy <= 1; dy++) {
//                 if((dx == 0) == (dy == 0)) continue; // This skips diagonal and non-movement cases

//                 int newX = current->cell.getPoint().getX() + dx;
//                 int newY = current->cell.getPoint().getY() + dy;

//                 if(newX < 0 || newX >= maze.getSize() || newY < 0 || newY >= maze.getSize()) continue; // Out of bounds
//                 if(!maze.getCell(newX, newY).isWalkable()) continue; // Unwalkable cell

//                 double tentative_g = current->g + 1.0;
//                 double h = computeH(Point(newX, newY), maze.getEndPoint().getPoint());
//                 double f = tentative_g + h;

//                 auto inList = [&](const vector<Node*>& list, const Point& point) -> Node* {
//                     for(Node* node : list) {
//                         if(node->cell.getPoint().getX() == point.getX() && node->cell.getPoint().getY() == point.getY()) {
//                             return node;
//                         }
//                     }
//                     return nullptr;
//                 };

//                 Node* successorInOpen = inList(openList, Point(newX, newY));
//                 Node* successorInClosed = inList(closedList, Point(newX, newY));

//                 if(successorInOpen && successorInOpen->f <= f) continue;
//                 if(successorInClosed && successorInClosed->f <= f) continue;

//                 Node* successor = new Node{maze.getCell(newX, newY), current, tentative_g, h, f};
//                 openList.push_back(successor);
//             }
//         }
//     }

//     vector<Cell> path;
//     if(goal) {
//         Node* current = goal;
//         while(current) {
//             path.push_back(current->cell);
//             current = current->parent;
//         }
//         reverse(path.begin(), path.end());
//     }

//     for(Node* node : openList) delete node;
//     for(Node* node : closedList) delete node;

//     return path;
// }