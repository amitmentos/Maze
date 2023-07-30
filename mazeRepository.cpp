#include "mazeRepository.hpp"
#include "maze.hpp"
#include <string.h>
#include <iostream>
using namespace std;


MazeRepository* MazeRepository::_instance = nullptr;

MazeRepository::MazeRepository() {}

MazeRepository* MazeRepository::getInstance() {
    if (!_instance) {
        _instance = new MazeRepository();
    }
    return _instance;
}

MazeRepository::~MazeRepository() {
    mazeList.clear();
}

void MazeRepository::saveMaze(Maze toAdd) {
    mazeList.push_back(toAdd);
}

Maze MazeRepository::getMaze(const std::string& name) {
    for (const Maze& maze : mazeList) {
        if (maze.getMazeName() == name) {
            return maze;
        }
    }
    return Maze(); // Return an empty maze if not found
}

void MazeRepository::showMaze(const std::string& name) {
    for (const Maze& maze : mazeList) {
        if (maze.getMazeName() == name) {
            // Display maze details (modify as per your Maze class implementation)
            std::cout << "Maze Name: " << maze.getMazeName() << std::endl;
            std::cout << "Maze Size: " << maze.getSize() << std::endl;
            // Add more details specific to your Maze class
            return;
        }
    }
    std::cout << "Maze not found." << std::endl;
}