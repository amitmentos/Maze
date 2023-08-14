#include "algorithm.hpp"
#include "maze.hpp"
#include "cell.hpp"
#include "point.hpp"
#include <unordered_map>
#include <utility>
#include <string.h>
#include <iostream>
#include <cstdlib>
#include <stack>
#include <algorithm>
#include <queue>
#include <cmath>
#include <vector>
using namespace std;



struct compare {
    bool operator()(const pair<int, pair<int, int>>& p1, const pair<int, pair<int, int>>& p2) {
        if (p1.first == p2.first) {
            return rand() % 2;
        }
        return p1.first < p2.first;
    }
};


Algorithm *AlgorithmList::getAlgorithm(const string &name)
{
    for (Algorithm *algorithm : algorithms)
    {
        if (algorithm->getAlgorithmName() == name)
            return algorithm;
    }
    return nullptr;
}



vector<Cell> AStar::solveMaze(const Maze &maze)
{
    priority_queue<Node *, vector<Node *>, CompareNode> openList;
    map<Cell *, Node *> allNodes;

    Node *startNode = new Node(maze.getCell(0, 0), nullptr, 0, heuristic(*(maze.getCell(0, 0)), *(maze.getCell(maze.getSize() - 1, maze.getSize() - 1))));
    openList.push(startNode);
    allNodes[maze.getCell(0, 0)] = startNode;

    while (!openList.empty())
    {
        Node *current = openList.top();
        openList.pop();

        if (current->cell == maze.getCell(maze.getSize() - 1, maze.getSize() - 1))
        {
            std::vector<Cell> path;
            while (current != nullptr)
            {
                path.push_back(*(current->cell));
                current = current->parent;
            }
            for (auto it : allNodes)
            {
                delete it.second;
            }
            std::reverse(path.begin(), path.end());
            return path;
        }

        vector<Cell *> neighbors = maze.getNeighbors(maze, current->cell);
        for (Cell *neighbor : neighbors)
        {
            if (neighbor->getType() == 1)
            { // assuming 1 is walkable
                float newG = current->g + 1;
                float newH = heuristic(*neighbor, *(maze.getCell(maze.getSize() - 1, maze.getSize() - 1)));
                if (allNodes.find(neighbor) == allNodes.end() || newG + newH < allNodes[neighbor]->f)
                {
                    Node *newNode = new Node(neighbor, current, newG, newH);
                    openList.push(newNode);
                    allNodes[neighbor] = newNode;
                }
            }
        }
    }

    // no solution
    for (auto it : allNodes)
    {
        delete it.second;
    }
    return std::vector<Cell>();
}

vector<Cell> DFS::solveMaze(const Maze &maze)
{

    int mazeSize = maze.getSize();
    Cell **mazeBoard = maze.getBoard();

    Cell *start = maze.getStartPoint();
    Cell *end = maze.getEndPoint();

    // Use a matrix to keep track of visited cells
    vector<vector<bool>> visited(mazeSize, vector<bool>(mazeSize, false));

    // Use a stack for DFS
    stack<Cell *> s;
    s.push(start);

    // We can also use a matrix to remember the parent of each cell
    vector<vector<Cell *>> parent(mazeSize, vector<Cell *>(mazeSize, nullptr));

    vector<int> dx = {0, 1, 0, -1};
    vector<int> dy = {1, 0, -1, 0};

    visited[start->getPoint().getX()][start->getPoint().getY()] = true;

    while (!s.empty())
    {
        Cell *curr = s.top();
        s.pop();

        // If we reach the end point, we stop
        if (curr == end)
        {
            vector<Cell> path;
            while (curr != start)
            {
                path.push_back(*curr);
                curr = parent[curr->getPoint().getX()][curr->getPoint().getY()];
            }
            path.push_back(*start);
            reverse(path.begin(), path.end());
            return path;
        }

        for (int i = 0; i < 4; i++)
        {
            int newX = curr->getPoint().getX() + dx[i];
            int newY = curr->getPoint().getY() + dy[i];

            // Check boundaries
            if (newX >= 0 && newX < mazeSize && newY >= 0 && newY < mazeSize)
            {
                if (!visited[newX][newY] && mazeBoard[newX][newY].isWalkable())
                {
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
#include <unordered_set>

vector<Cell> BFS::solveMaze(const Maze &maze)
{
    int size = maze.getSize();
    queue<Node> bfsQueue;
    unordered_set<int> visited;

    // Push starting point
    Cell start = *maze.getStartPoint();
    bfsQueue.push(Node(start, {start}));

    while (!bfsQueue.empty())
    {
        Node current = bfsQueue.front();
        bfsQueue.pop();

        if (current.cell.getX() == maze.getEndPoint()->getX() && current.cell.getY() == maze.getEndPoint()->getY())
        {
            return current.path; // We found the path
        }

        // Create a unique hash for the current cell based on its x and y values
        int hash = current.cell.getX() * size + current.cell.getY();
        if (visited.find(hash) != visited.end())
        {
            continue; // Skip if already visited
        }
        visited.insert(hash);

        // Get all the neighbors of the current cell
        vector<Point> directions = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        for (const Point &dir : directions)
        {
            int newX = current.cell.getX() + dir.getX();
            int newY = current.cell.getY() + dir.getY();

            // Check boundaries
            if (newX >= 0 && newY >= 0 && newX < size && newY < size)
            {
                Cell neighbor = *maze.getCell(newX, newY);
                if (neighbor.isWalkable())
                {
                    vector<Cell> newPath = current.path;
                    newPath.push_back(neighbor);
                    bfsQueue.push(Node(neighbor, newPath));
                }
            }
        }
    }

    return vector<Cell>();
}

vector<Cell> Prim::solveMaze(const Maze &maze)
{
    vector<vector<bool>> visited(maze.getSize(), vector<bool>(maze.getSize(), false));
    vector<vector<pair<int, int>>> parent(maze.getSize(), vector<pair<int, int>>(maze.getSize()));
    priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, compare> pq;

    // Start from the cell at position (0,0)
    pq.push(make_pair(0, make_pair(0, 0)));
    parent[0][0] = make_pair(-1, -1); 

    while (!pq.empty())
    {
        int x = pq.top().second.first;
        int y = pq.top().second.second;
        pq.pop();

        if (visited[x][y])
            continue;

        visited[x][y] = true;

        // Check if we've reached the goal
        if (x == maze.getSize() - 1 && y == maze.getSize() - 1)
            break;

        // Push all the unvisited neighbors of the current cell into the priority queue
        vector<pair<int, int>> directions = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}};
        for (auto direction : directions)
        {
            int newX = x + direction.first;
            int newY = y + direction.second;
            if (newX >= 0 && newY >= 0 && newX < maze.getSize() && newY < maze.getSize() && !visited[newX][newY] && maze.getCell(newX, newY)->getType() == 1)
            {
                parent[newX][newY] = make_pair(x, y);
                pq.push(make_pair(-maze.getCell(newX, newY)->getType(), make_pair(newX, newY)));
            }
        }
    }

    // Build the path from start to goal
    vector<Cell> path;
    pair<int, int> current = make_pair(maze.getSize() - 1, maze.getSize() - 1);

    while (!(current.first == 0 && current.second == 0))
    {
        path.push_back(*maze.getCell(current.first, current.second));
        current = parent[current.first][current.second];
        if (current.first == -1 && current.second == -1)
        {
            // This indicates that there's no valid path to the goal
            path.clear();
            break;
        }
    }
    if (!path.empty())
    {
        path.push_back(*maze.getCell(0, 0)); // push the start cell
        reverse(path.begin(), path.end());
    }

    if (!visited[maze.getSize() - 1][maze.getSize() - 1])
    {
        path.clear();
    }
    else
    {
        // If a valid solution was found, add the start cell to the path
        path.push_back(*maze.getCell(0, 0));
        reverse(path.begin(), path.end());
    }
    return path;
}
