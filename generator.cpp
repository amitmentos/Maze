#include "generator.hpp"
#include "algorithm.hpp"
#include <string.h>
#include <iostream>
#include <cstdlib>
using namespace std;

Maze RandomMaze2dGenerator::generate(int size)
{
    Maze newMaze(size, "RandomMaze");
    Cell **board = newMaze.getBoard();

    // Randomly populate the maze with walls (0) and paths (1).
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            // Cell newCell = new Cell;
            newMaze.getCell(i, j).setType(rand() % 2);
        }
    }

    // Ensure start and end points are walkable.
    newMaze.getCell(0, 0).setType(1);
    newMaze.getCell(size - 1, size - 1).setType(1);

    // If there's no solution, regenerate.
    while (hasSolution(newMaze) == false)
    {
        newMaze = generate(size);
    }

    return newMaze;
}

bool RandomMaze2dGenerator::hasSolution(const Maze &maze)
{
    DFS dfsSolver;
    vector<Cell> solutionPath = dfsSolver.solveMaze(maze);
    if (solutionPath[0].getType()== false)
    {
        false;
    }
    
    return true;
}



// float Maze2dGenerator::measureAlgorithmTime() {
//     auto start = chrono::high_resolution_clock::now();
//     generate();
//     auto end = std::chrono::high_resolution_clock::now();
//     std::chrono::duration<float> duration = end - start;
//     return duration.count();
// }

//     Maze SimpleMaze2dGenerator::generate(int size) {
//         // Implementation of the generate function using a specific algorithm
//         // You should replace this with the actual implementation using the provided Maze and Algorithm parameters
//         // ...

//         return maze; // Return the generated Maze
//     }

//     void SimpleMaze2dGenerator::compress(Maze maze) {
//         // Implementation of the compress function
//         // You should replace this with the actual implementation using the provided Maze parameter
//         // ...
//     }