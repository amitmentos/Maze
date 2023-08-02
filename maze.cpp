#include "maze.hpp"
#include <string.h>
#include <iostream>
using namespace std;

Maze::Maze(int size, const std::string &name) : size(size), mazeName(name)
{
    mazeBoard = new Cell *[size];
    for (int i = 0; i < size; i++)
    {
        mazeBoard[i] = new Cell[size];
    }
    startPoint = new Cell();
    endPoint = new Cell();
    userPoint = new Cell();
    this->startPoint->setX(0);
    this->startPoint->setY(0);
    this->endPoint->setX(size - 1);
    this->endPoint->setY(size - 1);
    this->userPoint->setX(0);
    this->userPoint->setY(0);
}

Maze::Maze(const Maze &toCopy) : size(toCopy.size), mazeName(toCopy.mazeName)
{
    // Copy the maze board
    mazeBoard = new Cell *[size];
    for (int i = 0; i < size; i++)
    {
        mazeBoard[i] = new Cell[size];
        for (int j = 0; j < size; j++)
        {
            mazeBoard[i][j] = toCopy.mazeBoard[i][j];
        }
    }

    startPoint = toCopy.startPoint;
    endPoint = toCopy.endPoint;

    if (toCopy.userPoint != nullptr)
    {
        userPoint = toCopy.userPoint;
    }
    else
    {
        userPoint = nullptr;
    }
}

Maze::~Maze()
{
    for (int i = 0; i < size; i++)
    {
        delete[] mazeBoard[i];
    }
    delete[] mazeBoard;
    // if(startPoint){
    //     delete startPoint;
    // }

    // delete endPoint;
    // cout<<"asd";
    // delete userPoint;
}

void Maze::display()
{
    for (size_t i = 0; i < (size * 2) + 4; i++)
    {
        cout << "-";
    }
    cout << endl;
    for (int i = 0; i < size; i++)
    {
        cout << "|  ";
        for (int j = 0; j < size; j++)
        {
            if (mazeBoard[i][j].getType() == 0)
            {
                cout << "#"
                     << " ";
            }
            else
            {
                if (this->getUserPoint()->getX() == i && this->getUserPoint()->getY() == j)
                {
                    cout << "P"
                         << " ";
                }
                else
                {
                    cout << " "
                         << " ";
                }
            }
        }
        cout << "|" << endl;
    }
    for (size_t i = 0; i < (size * 2) + 4; i++)
    {
        cout << "-";
    }
    cout << endl;
}