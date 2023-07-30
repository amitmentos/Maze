#include "system.hpp"
#include <string.h>
#include <iostream>
using namespace std;

GameSystem* GameSystem::_instance = nullptr;


GameSystem::~GameSystem(){}

GameSystem* GameSystem::getInstance() {
    if (!_instance) {
        _instance = new GameSystem();
    }
    return _instance;
}

void GameSystem::exit() {
    delete _instance;
    _instance = nullptr;
}

void GameSystem::gameStart() {
    if (currentState == MENU) {
        std::cout << "Game is starting..." << std::endl;
        currentState = PLAYING;


    }
}

void GameSystem::gameReset() {
    if (currentState == PLAYING) {
        std::cout << "Resetting the game..." << std::endl;
        currentState = MENU;
    } 
}

void GameSystem::saveMaze(Maze& maze) {
    myMazes.saveMaze(maze);
}

Maze& GameSystem::chooseMaze(const std::string& name) {
    for (Maze maze : myMazes.getMazeList()) {
        if (maze.getMazeName() == name) {
            return maze;
        }
    }
    cout<<"maze wasn't found!"; 
}


void GameSystem::listFiles() {
    std::cout << "List of mazes in the repository:" << std::endl;
    for (const Maze& maze : myMazes.getMazeList()) {
        std::cout << maze.getMazeName() << std::endl;
    }
}

