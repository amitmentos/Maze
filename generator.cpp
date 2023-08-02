#include "generator.hpp"
#include "algorithm.hpp"
#include <string.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

// float SimpleMaze2dGenerator::measureAlgorithmTime(int size, string mazeName) {
//     auto start = chrono::high_resolution_clock::now();
//     generate(size,mazeName);
//     auto end = std::chrono::high_resolution_clock::now();
//     std::chrono::duration<float> duration = end - start;
//     return duration.count();
// }

// void SimpleMaze2dGenerator::compress(Maze& maze) {
//     // Implementation of the compress function
//     // You should replace this with the actual implementation using the provided Maze parameter
//     // ...
// }

Maze SimpleMaze2dGenerator::generate(int size, string mazeName)
{
    srand(static_cast<unsigned int>(std::time(nullptr)));
    Maze newMaze(size, mazeName);
    // Cell **board = newMaze.getBoard();

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

    // while (hasSolution(newMaze) == false)
    // {
    //     newMaze = generate(size, mazeName);
    // }
    return newMaze;
}

bool SimpleMaze2dGenerator::hasSolution(const Maze &maze)
{
    BFS dfsSolver;
    vector<Cell> solutionPath = dfsSolver.solveMaze(maze);
    if (solutionPath.empty()== true)
    {
        return false;
    }
    return true;
}

std::vector<std::string> MazeCompressor::compress(const Maze &maze)
{
    int size = maze.getSize();
    string compressed = "";

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
    vector<string> toReturn  = {maze.getMazeName(),compressed};
    return toReturn;
}


// #include "generator.hpp"
// #include "algorithm.hpp"
// #include <string.h>
// #include <iostream>
// #include <cstdlib>
// #include <ctime>
// using namespace std;

// // float SimpleMaze2dGenerator::measureAlgorithmTime(int size, string mazeName) {
// //     auto start = chrono::high_resolution_clock::now();
// //     generate(size,mazeName); 
// //     auto end = std::chrono::high_resolution_clock::now();
// //     std::chrono::duration<float> duration = end - start;
// //     return duration.count();
// // }



// void SimpleMaze2dGenerator::compress(Maze& maze) {
//     // Implementation of the compress function
//     // You should replace this with the actual implementation using the provided Maze parameter
//     // ...
// }

// Maze SimpleMaze2dGenerator::generate(int size, string mazeName)
// {
//     srand(static_cast<unsigned int>(std::time(nullptr)));
//     Maze newMaze(size, mazeName);
//     // Cell **board = newMaze.getBoard();
    
//     for (int i = 0; i < size; i++)
//     {
//         for (int j = 0; j < size; j++)
//         {
//             newMaze.getCell(i, j)->setType(rand() % 2);
//             newMaze.getCell(i,j)->setX(i);
//             newMaze.getCell(i,j)->setY(j);
//         }
//     }

//     newMaze.getCell(0, 0)->setType(1);
//     newMaze.getCell(size - 1, size - 1)->setType(1);
//     while (hasSolution(newMaze) == false)
//     {
//         cout<<"333333333";
//         newMaze = generate(size, mazeName);
//     }
//     return newMaze;
// }

// bool SimpleMaze2dGenerator::hasSolution(const Maze &maze)
// {
//     BFS dfsSolver;
//     vector<Cell> solutionPath = dfsSolver.solveMaze(maze);
//     if (solutionPath.empty()== true)
//     {
//         cout<<solutionPath.empty();
//         return false;
//     }
//     return true;
// }


