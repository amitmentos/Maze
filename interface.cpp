#include <string>
#include <iostream>
using namespace std;
#include "interface.hpp"

UserInterface::~UserInterface()
{
}

bool checkNewPoint(int newX, int newY, int mazeSize, Maze &mazeBoard)
{
    // cout << newX << newY << endl<<flush;
    if (newX < 0 || newY < 0 || newX >= mazeSize || newY >= mazeSize || !mazeBoard.getCell(newX, newY)->isWalkable())
    {
        cout << "invaild command!!" << endl;
        return false;
    }
    return true;
}

GraphicalInterface::GraphicalInterface()
{
}

GraphicalInterface::~GraphicalInterface()
{
}

void GraphicalInterface::displayMaze(Maze *maze)
{
    maze->display();
}

void GraphicalInterface::displaySolution(MazeSolution solution)
{
    solution.display();
}

void GraphicalInterface::update(myCommands &cmd)
{
}

void GraphicalInterface::setCommand(myCommands &cmd)
{
    toDo = cmd;
}

Command::~Command()
{
}

void GraphicalInterface::execute(myCommands &cmd, Maze *currMaze)
{
    int newX, newY;
    switch (toDo)
    {
    case Up:
    {
        newX = currMaze->getUserPoint()->getX() - 1;
        newY = currMaze->getUserPoint()->getY();
        if (checkNewPoint(newX, newY, currMaze->getSize(), *currMaze))
        {
            currMaze->setUserPoint(newX, newY);
        };
        break;
    }
    case Down:
        newX = currMaze->getUserPoint()->getX() + 1;
        newY = currMaze->getUserPoint()->getY();
        if (checkNewPoint(newX, newY, currMaze->getSize(), *currMaze))
        {
            currMaze->setUserPoint(newX, newY);
        };
        break;
    case Left:
        newX = currMaze->getUserPoint()->getX();
        newY = currMaze->getUserPoint()->getY() - 1;
        if (checkNewPoint(newX, newY, currMaze->getSize(), *currMaze))
        {
            currMaze->setUserPoint(newX, newY);
        };
        break;

    case Right:
        newX = currMaze->getUserPoint()->getX();
        newY = currMaze->getUserPoint()->getY() + 1;
        if (checkNewPoint(newX, newY, currMaze->getSize(), *currMaze))
        {
            currMaze->setUserPoint(newX, newY);
        };
        break;
    default:
        cout << "Invalid command!\n";
    }
    if (newX == currMaze->getEndPoint()->getX() && newY == currMaze->getEndPoint()->getY())
    {
        cout << "              .-=========-." << endl;
        cout << "              \\'-=======-'/" << endl;
        cout << "              _|   .=.   |_" << endl;
        cout << "             ((|  {{1}}  |))" << endl;
        cout << "              \\|   /|\\   |/" << endl;
        cout << "               \\__ '`' __/" << endl;
        cout << "                 _`) (`_" << endl;
        cout << "      Winner!  _/_______\\_" << endl;
        cout << "              /___________\\" << endl;
        currMaze->setUserPoint(0,0);
        cout << "---------------------------------------------------------------------------------"<<endl;
    }
}
