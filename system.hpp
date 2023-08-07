#pragma once
#include <string.h>
#include <iostream>
using namespace std;
#include <vector>
#include <filesystem>
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
    static GameSystem* game_instance;
    Status currentState;
    Maze* currentMaze;
    SolutionRepository* mySolutions;
    MazeRepository* myMazes;
    GameSystem();

public:
    static GameSystem* getInstance();
    ~GameSystem();
    void listFiles();
    void showMazes(int index);
    void showCurrent(){currentMaze->display();};
    Maze chooseMaze(const string& name);
    // void changeMaze();
    void saveMaze(Maze* maze);
    virtual void gameStart();
    virtual void gameReset();
    void exit();
    void setCurrentMaze(Maze* toSet){currentMaze=toSet;};
    Maze loadMyMaze(int index);
    Maze loadMyMazeFromRepository(int index);
    Maze* getCurrentMaze(){return currentMaze;}
    SolutionRepository* getmySolutions(){return mySolutions;}
    MazeRepository* getMyMazes(){return myMazes;}
    void listFilesInDirectory(const std::string &path);
    void listTxtFilesInDirectory();
    void listTxtFilesInDirectory(vector<string> &txtFiles);
    void getFileSize(const string& path);
    void saveMazeExistF(Maze* maze);
    void showMyMazes(){myMazes->showMazeList();}
};


