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
    virtual void execute(Command&) =0;
    myCommands getCommand(){return toDo;}
};



class UserInterface
{
public:
    virtual ~UserInterface();
    virtual void setCommand(Command& cmd)= 0;
    virtual void invokeCommand(Command& cmd) =0;
    virtual void update(Command& cmd) = 0;
};

UserInterface::~UserInterface()
{
}


class GraphicalInterface : public UserInterface, public Command
{
public:
    GraphicalInterface();
    ~GraphicalInterface();
    virtual void displayMaze(Maze);
    virtual void displaySolution(MazeSolution);
    virtual void update(Command& cmd);
    virtual void execute(Command&);
    virtual void invokeCommand(Command& cmd);
    virtual void setCommand(Command& cmd);
};

