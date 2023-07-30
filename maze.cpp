#include "maze.hpp"

Maze::Maze(int size, const std::string& name) : size(size), mazeName(name) {
        mazeBoard = new int*[size];
        for (int i = 0; i < size; i++) {
            mazeBoard[i] = new int[size];
        }
    }

Maze::~Maze() {
        for (int i = 0; i < size; i++) {
            delete[] mazeBoard[i];
        }
        delete[] mazeBoard;
    }

void Maze::display() const {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                std::cout << mazeBoard[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }