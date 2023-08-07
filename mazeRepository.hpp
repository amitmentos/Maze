#pragma once
#include <string.h>
#include <iostream>
#include <vector>
#include "maze.hpp"
using namespace std;

class MazeRepository {
private:
    static MazeRepository* maze_instance;
    vector<Maze> mazeList;
    MazeRepository();

public:
    static MazeRepository* getInstance();
    ~MazeRepository();
    void saveMaze(Maze* toAdd);
    Maze getMaze(const string& name);
    Maze getMaze(int index);
    Maze getMazeFromList(int index){return mazeList[index];}
    void showMaze(const string& name);
    bool showAllMazes(int index);
    vector<Maze> getMazeList(){return mazeList;}
    void saveMazeExist(Maze *toAdd, int index);
    void saveMazeToRepository(Maze toAdd);
    void showMazeList();
};