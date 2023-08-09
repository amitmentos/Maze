#include "mazeSolution.hpp"
#include <vector>
#include <algorithm>

MazeSolution::MazeSolution() {}

MazeSolution& MazeSolution::operator=(const MazeSolution& other) {
    if (this != &other) {
        name = other.name;
        path = other.path;
    }
    return *this;
}

// MazeSolution::MazeSolution(const Maze &m, Algorithm *alg) : maze(m), algorithms(alg) {}
void MazeSolution::display()
{
    for (int i = 0; i < this->getPath().size(); i++)
    {
        std::cout << "(" << this->getPath()[i].getX() << ", " << this->getPath()[i].getY() << ") ";
    }
    cout << endl;

    for (int i = 0; i < (this->getPath()[0,0].getX())*2 + 3; i++)
    {
        cout << "-";
    }
    cout << endl;

    for (int i = 0; i < this->getPath()[0,0].getX(); i++)
    {
        cout << "| ";
        for (int j = 0; j < this->getPath()[0,0].getX(); j++)
        {
            bool isPathCell = false;
            for (const Cell& pathCell : this->getPath())
            {
                if (pathCell.getX() == i && pathCell.getY() == j)
                {
                    isPathCell = true;
                    break;
                }
            }

            if (isPathCell)
            {
                cout << "#"
                    << " ";
            }
            else
            {
                cout << " "
                     << " ";
            }
        }
        cout << "|" << endl;
    }

    for (int i = 0; i < (this->getPath()[0,0].getX())*2 + 3; i++)
    {
        cout << "-";
    }
    cout << endl;
}

