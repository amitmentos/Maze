#include "generator.hpp"
#include "algorithm.hpp"
#include "mazeSolution.hpp"
#include "system.hpp"
#include <string.h>
#include <chrono>
#include <math.h>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <sstream>
using namespace std;

void addToFrontier(const Maze &maze, vector<pair<int, int>> &frontier, int x, int y);
vector<pair<int, int>> getNeighbors(int x, int y, int size);
bool isValid(int x, int y, int size);

std::chrono::high_resolution_clock::time_point startTime;
std::chrono::high_resolution_clock::time_point endTime;

// Function to start measuring time
void startTimer()
{
    startTime = std::chrono::high_resolution_clock::now();
}

// Function to stop measuring time and print the elapsed time
void stopTimer()
{
    endTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> elapsedTime = endTime - startTime;
    std::cout << "Algorithm took " << elapsedTime.count() << " seconds." << std::endl;
}

bool MazeCompressor::writeStringToFile(const vector<string> &content)
{
    std::ofstream file("file.txt", ios::app);
    if (!file.is_open())
    {
        cerr << "Error: Unable to open file." << std::endl;
        return false;
    }

    file << content[0] << "," << content[1] << content[2] << std::endl;

    file.close();
    return true;
}

Maze MazeCompressor::decompress(int index)
{
    std::ifstream file("file.txt");
    if (!file.is_open())
    {
        throw std::runtime_error("Error: Unable to open file.");
    }

    // Find the line at the given index
    std::string line;
    for (int i = 0; i <= index; i++)
    {
        if (!std::getline(file, line))
        {
            throw std::invalid_argument("Invalid index: Maze not found.");
        }
    }

    file.close();

    // Now, decompress the maze from the line
    std::istringstream iss(line);
    std::string mazeName, sizeStr, compressed;
    int size;
    if (std::getline(iss, mazeName, ','))
    {
        if (!std::getline(iss, sizeStr, ','))
        {
            throw std::invalid_argument("Invalid compressed maze format: Unable to read size.");
        }
        size = std::stoi(sizeStr);
        if (!std::getline(iss, compressed))
        {
            throw std::invalid_argument("Invalid compressed maze format");
        }
        std::istringstream issCompressed(compressed);
        std::string valueStr, countStr;
        int value, count;
        std::vector<int> cells;
        while (std::getline(issCompressed, valueStr, ',') && std::getline(issCompressed, countStr, ','))
        {
            try
            {
                value = std::stoi(valueStr);
                count = std::stoi(countStr);
            }
            catch (const std::invalid_argument &ia)
            {
                throw std::invalid_argument("Invalid compressed maze format");
            }

            cells.insert(cells.end(), count, value);
        }
        // Create the maze with the decompressed cells
        Maze decompressedMaze(size, mazeName);
        int x = 0;
        int y = 0;
        for (int cellValue : cells)
        {
            decompressedMaze.setCell(x, y, cellValue);
            y++;
            if (y == size)
            {
                y = 0;
                x++;
            }
        }
        return decompressedMaze;
    }
    else
    {
        // Invalid compressed maze
        throw std::invalid_argument("Invalid compressed maze format");
    }
}

// float SimpleMaze2dGenerator::measureAlgorithmTime(Maze& maze){

// }

Maze SimpleMaze2dGenerator::generate(int size, string mazeName)
{
    startTimer();
    srand(static_cast<unsigned int>(std::time(nullptr)));
    Maze newMaze(size, mazeName);

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            newMaze.getCell(i, j)->setType(rand() % 2);
            newMaze.getCell(i, j)->setX(i);
            newMaze.getCell(i, j)->setY(j);
        }
    }
    int count = 1;
    newMaze.getCell(0, 0)->setType(1);
    newMaze.getCell(size - 1, size - 1)->setType(1);
    do
    {
        cout << count++ << endl;
        newMaze = generateNewMaze(size, mazeName);
    } while (!hasSolution(newMaze));
    stopTimer();
    return newMaze;
}
static int counter1 = 0;

bool SimpleMaze2dGenerator::hasSolution(const Maze &maze)
{
    Prim bfsSolver;
    MazeSolution solutionPath;
    GameSystem *myGame = GameSystem::getInstance();
    solutionPath.setPath(bfsSolver.solveMaze(maze));
    ;
    if (solutionPath.getPath().empty())
    {
        return false;
    }

    myGame->getmySolutions()->saveSolution(maze.getMazeName(), solutionPath);
    myGame->getmySolutions()->showSolution(maze.getMazeName());
    std::cout << std::endl;
    return true;
}

std::vector<std::string> MazeCompressor::compress(const Maze &maze)
{
    int size = maze.getSize();
    string compressed = "";

    // Append the size of the maze to the compressed string
    compressed += to_string(size) + ",";

    // Convert 2D maze into 1D array
    vector<int> maze1D;
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            maze1D.push_back(maze.getCell(i, j)->getType());
        }
    }
    for (size_t i = 0; i < maze1D.size(); i++)
    {
        int count = 1;
        while (i < maze1D.size() - 1 && maze1D[i] == maze1D[i + 1])
        {
            count++;
            i++;
        }
        compressed += to_string(maze1D[i]) + "," + to_string(count) + ",";
    }
    vector<string> toReturn = {maze.getMazeName(), compressed};
    return toReturn;
}

Maze SimpleMaze2dGenerator::generateNewMaze(int size, string mazeName)
{
    srand(static_cast<unsigned int>(std::time(nullptr)));
    Maze newMaze(size, mazeName);
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            newMaze.getCell(i, j)->setType(rand() % 2);
            newMaze.getCell(i, j)->setX(i);
            newMaze.getCell(i, j)->setY(j);
        }
    }
    newMaze.getCell(0, 0)->setType(1);
    newMaze.getCell(size - 1, size - 1)->setType(1);
    return newMaze;
}

// Adds unvisited walls of a cell to the frontier
void addToFrontier(const Maze &maze, vector<pair<int, int>> &frontier, int x, int y)
{
    int size = maze.getSize();

    // Define directions: North, South, East, West
    vector<pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};

    for (const auto &dir : directions)
    {
        int nx = x + dir.first;
        int ny = y + dir.second;

        // Check if the neighbor is within bounds and unvisited
        if (isValid(nx, ny, size) && maze.getCell(nx, ny)->getType() == 0)
        {
            maze.getCell(nx, ny)->setType(2); // Mark the wall as a frontier
            frontier.push_back(make_pair(nx, ny));
        }
    }
}

// Returns a vector of neighboring cell coordinates
vector<pair<int, int>> getNeighbors(int x, int y, int size)
{
    vector<pair<int, int>> neighbors;

    vector<pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};

    for (const auto &dir : directions)
    {
        int nx = x + dir.first;
        int ny = y + dir.second;

        if (isValid(nx, ny, size))
        {
            neighbors.push_back(make_pair(nx, ny));
        }
    }

    return neighbors;
}

// Checks if a cell coordinate is valid within the maze
bool isValid(int x, int y, int size)
{
    return x >= 0 && x < size && y >= 0 && y < size;
}

Maze myMaze2dGenerator::generate(int size, string mazeName)
{
    startTimer();
    srand(static_cast<unsigned int>(std::time(nullptr)));
    Maze newMaze(size, mazeName);

    // Initialize the maze with all passages (type 1)
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            newMaze.getCell(i, j)->setType(1);
            newMaze.getCell(i, j)->setX(i);
            newMaze.getCell(i, j)->setY(j);
        }
    }

    int startX = 0; // Starting cell's x-coordinate
    int startY = 0; // Starting cell's y-coordinate

    // Set the starting cell as a passage and add its walls to the frontier
    newMaze.getCell(startX, startY)->setType(1);
    vector<pair<int, int>> frontier;
    addToFrontier(newMaze, frontier, startX, startY);

    // Continue until the frontier is empty and a path is found
    while (!frontier.empty())
    {
        int randomIndex = rand() % frontier.size();
        int currentX = frontier[randomIndex].first;
        int currentY = frontier[randomIndex].second;
        frontier.erase(frontier.begin() + randomIndex);

        vector<pair<int, int>> neighbors = getNeighbors(currentX, currentY, size);
        vector<pair<int, int>> connectedNeighbors;
        for (const auto &neighbor : neighbors)
        {
            int nx = neighbor.first;
            int ny = neighbor.second;
            if (isValid(nx, ny, size) && newMaze.getCell(nx, ny)->getType() == 1)
            {
                connectedNeighbors.push_back(neighbor);
            }
        }

        if (!connectedNeighbors.empty())
        {
            int randomNeighborIndex = rand() % connectedNeighbors.size();
            int chosenX = connectedNeighbors[randomNeighborIndex].first;
            int chosenY = connectedNeighbors[randomNeighborIndex].second;

            newMaze.getCell(currentX, currentY)->setType(1);
            newMaze.getCell(chosenX, chosenY)->setType(1);

            addToFrontier(newMaze, frontier, chosenX, chosenY);
        }
    }
    Prim bfsSolver;
    // Generate the solution path using BFS
    vector<Cell> solutionPath = bfsSolver.solveMaze(newMaze);
    MazeSolution solutionPathM;
    GameSystem *myGame = GameSystem::getInstance();
    solutionPathM.setPath(solutionPath);
    myGame->getmySolutions()->saveSolution(newMaze.getMazeName(), solutionPathM);
    myGame->getmySolutions()->showSolution(newMaze.getMazeName());
    // Randomly change cells not in the solution path to 0 or 1
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (newMaze.getCell(i, j)->getType() == 1)
            {
                bool isOnPath = false;

                for (const Cell &cell : solutionPath)
                {
                    if (cell.getX() == i && cell.getY() == j)
                    {
                        isOnPath = true;
                        break;
                    }
                }

                if (!isOnPath)
                {
                    newMaze.getCell(i, j)->setType(rand() % 2);
                }
            }
        }
    }

    // Set the start and end points
    newMaze.getCell(0, 0)->setType(1);
    newMaze.getCell(size - 1, size - 1)->setType(1);
    stopTimer();
    return newMaze;
}
