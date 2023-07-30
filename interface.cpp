#include <string>
#include <iostream>
using namespace std;
#include "interface.hpp"

GraphicalInterface::GraphicalInterface(){
}

GraphicalInterface::~GraphicalInterface(){
}

void GraphicalInterface::displayMaze(Maze maze)
{
    maze.display();
}

void GraphicalInterface::displaySolution(MazeSolution solution)
{
    solution.display();
}

void GraphicalInterface::update(Command& cmd){
}

void GraphicalInterface::setCommand(Command& cmd){
    toDo = cmd.getCommand();
}

void GraphicalInterface::invokeCommand(Command& cmd)
{
    cmd.execute(cmd);
}



Command::~Command()
{
}

void GraphicalInterface::execute(Command& cmd){

}
