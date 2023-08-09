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
        userPoint = new Cell(*(toCopy.userPoint));
    }
    else
    {
        userPoint = nullptr;
    }
}

Maze::~Maze()
{
    // if (mazeBoard)
    // {
    //     for (int i = 0; i < size; i++)
    //     {
    //         delete[] mazeBoard[i];
    //     }
    //     delete[] mazeBoard;
    // }
}

void Maze::display()
{
    for (size_t i = 0; i < (size * 2) + 2; i++)
    {
        cout << "_";
    }
    cout << endl;
    for (int i = 0; i < size; i++)
    {
        cout << "| ";
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
                    cout << "§"
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
    for (size_t i = 0; i < (size * 2) + 2; i++)
    {
        cout << "-";
    }
    cout << endl;
}

void Maze::setCell(int x, int y, int cellValue)
{
    if (x < 0 || x >= size || y < 0 || y >= size)
    {
        throw std::out_of_range("Invalid cell coordinates: Out of range.");
    }
    mazeBoard[x][y].setType(cellValue);
}

vector<Cell *> Maze::getNeighbors(const Maze &maze, Cell *cell) const
{
    std::vector<Cell *> neighbors;
    int x = cell->getX();
    int y = cell->getY();

    if (x > 0 && maze.getCell(x - 1, y)->getType() == 1)
    {
        neighbors.push_back(maze.getCell(x - 1, y));
    }

    if (x < maze.getSize() - 1 && maze.getCell(x + 1, y)->getType() == 1)
    {
        neighbors.push_back(maze.getCell(x + 1, y));
    }

    if (y > 0 && maze.getCell(x, y - 1)->getType() == 1)
    {
        neighbors.push_back(maze.getCell(x, y - 1));
    }

    if (y < maze.getSize() - 1 && maze.getCell(x, y + 1)->getType() == 1)
    {
        neighbors.push_back(maze.getCell(x, y + 1));
    }

    return neighbors;
}