#include "system.hpp"
#include <string.h>
#include <iostream>
#include <filesystem>
using namespace std;

GameSystem *GameSystem::game_instance = nullptr;

GameSystem::~GameSystem() {}
GameSystem::GameSystem()
{
    mySolutions = SolutionRepository::getInstance();
    myMazes = MazeRepository::getInstance();
    currentMaze = nullptr;
}
GameSystem *GameSystem::getInstance()
{
    if (!game_instance)
    {
        game_instance = new GameSystem();
    }
    return game_instance;
}

void GameSystem::exit()
{
    delete game_instance;
    game_instance = nullptr;
}

void GameSystem::gameStart()
{
    if (1)
    {
        int flagKeepPlay=1;
        cout << "Game is starting..." << std::endl;
        currentState = PLAYING;
        do
        {
            this->currentMaze->display();
            cout << "what would you like to do? (0- UP | 1- Down | 2- Left | 3- Right | 4- Stop Play)" << endl;
            int inputCommand;
            cin >> inputCommand;
            switch (inputCommand)
            {
            case 0:
                toDo = Up;
                break;
            case 1:
                toDo = Down;
                break;
            case 2:
                toDo = Left;
                break;
            case 3:
                toDo = Right;
                break;
            case 4:
                flagKeepPlay =0;
                break;
            default:
                cout << "Invalid command!\n";
            }
            if(inputCommand!=4){
                execute(toDo, this->currentMaze);
            }
        } while (flagKeepPlay);
    }
}

void GameSystem::gameReset()
{
    if (currentState == PLAYING)
    {
        std::cout << "Resetting the game..." << std::endl;
        currentMaze->setUserPoint(currentMaze->getStartPoint()->getX(), currentMaze->getStartPoint()->getY());
    }
}

void GameSystem::saveMaze(Maze *maze)
{
    myMazes->saveMaze(maze);
}

Maze *GameSystem::chooseMaze(const std::string &name)
{
    for (Maze *maze : myMazes->getMazeList())
    {
        if (maze->getMazeName() == name)
        {
            return maze;
        }
    }
    cout << "maze wasn't found!";
    return nullptr;
}

void GameSystem::listFiles()
{
    std::cout << "List of mazes in the repository:" << std::endl;
    for (Maze *maze : myMazes->getMazeList())
    {
        std::cout << maze->getMazeName() << std::endl;
    }
}

void GameSystem::showMazes()
{

    myMazes->showAllMazes();
}

Maze GameSystem::loadMyMaze(int index)
{
    return myMazes->getMaze(index);
}


void GameSystem::listFilesInDirectory(const std::string &path)
{
    for (const auto &entry : std::filesystem::directory_iterator(path))
    {
        std::cout << entry.path() << std::endl;
    }
}