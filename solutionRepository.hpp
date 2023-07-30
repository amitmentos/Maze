#pragma once
#include <iostream>
#include <string>
#include <map>
#include "mazeSolution.hpp"
using namespace std; 

class SolutionRepository {
private:
    static SolutionRepository* _instance;
    map<string, MazeSolution*> solutions;
    MazeSolution currrentSolution;
    SolutionRepository();

public:
    static SolutionRepository* getInstance();
    ~SolutionRepository();
    bool saveSolution(const string& mazeName, MazeSolution* toAdd);
    MazeSolution* getSolution(const string& name);
    void showSolution(const string& name);
};