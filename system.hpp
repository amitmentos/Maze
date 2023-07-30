#pragma once
#include <string.h>
#include <iostream>
using namespace std;
#include <vector>
#include "interface.hpp"
#include "solutionRepository.hpp"
#include "mazeRepository.hpp"
#include "maze.hpp"

enum Status {
    MENU,
    Start,
    PLAYING,
    GAME_OVER
};

class GameStatus
{
public:
    virtual void gameStart() = 0;
    virtual void gameReset() = 0;
    virtual void exit() = 0 ;
    virtual ~GameStatus() {}
};


class GameSystem:public GraphicalInterface, public GameStatus{
private:
    static GameSystem* _instance;
    Status currentState;
    Maze currentMaze;
    SolutionRepository mySolutions;
    MazeRepository myMazes;
    GameSystem();

public:
    static GameSystem* getInstance();
    ~GameSystem();
    void listFiles();
    Maze& chooseMaze(const string& name);
    void changeMaze();
    void saveMaze(Maze& maze);
    virtual void gameStart();
    virtual void gameReset();
    void exit();
};

