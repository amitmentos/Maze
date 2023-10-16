#pragma once
#include "maze.hpp"
#include "mazeSolution.hpp"
#include <string>
#include <iostream>
using namespace std;

enum myCommands{Up, Down, Left, Right};

class Command
{
protected:
    myCommands toDo;

public:
    virtual ~Command();
    virtual void execute(myCommands&, Maze*) =0;
    myCommands getCommand(){return toDo;}
};



class UserInterface
{
public:
    virtual ~UserInterface();
    virtual void setCommand(myCommands& cmd)= 0;
    virtual void update(myCommands& cmd) = 0;
};




class GraphicalInterface : public UserInterface, public Command
{
public:
    GraphicalInterface();
    GraphicalInterface(myCommands& toInsert){toDo = toInsert;};
    ~GraphicalInterface();
    virtual void displayMaze(Maze*);
    virtual void displaySolution(MazeSolution);
    virtual void update(myCommands& cmd);
    virtual void execute(myCommands&, Maze*);
    virtual void setCommand(myCommands& cmd);
};

