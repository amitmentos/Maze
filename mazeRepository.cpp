#include "mazeRepository.hpp"
#include "maze.hpp"
#include "generator.hpp"
#include <string.h>
#include <iostream>
using namespace std;

MazeRepository *MazeRepository::maze_instance = nullptr;

MazeRepository::MazeRepository() {}

MazeRepository *MazeRepository::getInstance()
{
    if (!maze_instance)
    {
        maze_instance = new MazeRepository();
    }
    return maze_instance;
}

MazeRepository::~MazeRepository()
{
    for (Maze *maze : mazeList)
    {
        delete maze;
    }
}

void MazeRepository::saveMaze(Maze *toAdd)
{
    MazeCompressor compressor;
    vector<string> compressedMaze = compressor.compress(*toAdd);
    cout << "Maze Name: " << compressedMaze[0] << endl;
    cout << "Compressed Maze: " << compressedMaze[1] << endl;
    // mazeList.push_back(toAdd);
}

Maze *MazeRepository::getMaze(const string &name)
{
    for (Maze *maze : mazeList)
    {
        if (maze->getMazeName() == name)
        {
            return maze;
        }
    }
    return nullptr;
}

void MazeRepository::showMaze(const std::string &name)
{
    for (Maze *maze : mazeList)
    {
        if (maze->getMazeName() == name)
        {
            // Display maze details (modify as per your Maze class implementation)
            std::cout << "Maze Name: " << maze->getMazeName() << std::endl;
            std::cout << "Maze Size: " << maze->getSize() << std::endl;
            // Add more details specific to your Maze class
            return;
        }
    }
    std::cout << "Maze not found." << std::endl;
}

void MazeRepository::showAllMazes()
{
    if (mazeList.empty())
    {
        cout << "No mazes in the repository.\n";
        return;
    }

    cout << "All mazes in the repository:\n";
    int index = 1;
    for (Maze *maze : mazeList)
    {
        cout << index << "- " << maze->getMazeName() << endl;
        index++;
    }
}

Maze *MazeRepository::getMaze(int index)
{
    return mazeList[index];
}