#pragma once
#include <string.h>
#include <iostream>
#include <vector>
using namespace std;

class MazeRepository {
private:
    static MazeRepository* _instance;
    vector<Maze> mazeList;
    MazeRepository();

public:
    static MazeRepository* getInstance();
    ~MazeRepository();
    void saveMaze(Maze toAdd);
    Maze getMaze(const string& name);
    void showMaze(const string& name);
    vector<Maze> getMazeList(){return mazeList;}
};