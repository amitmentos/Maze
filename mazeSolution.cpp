#include "mazeSolution.hpp"

MazeSolution::MazeSolution() : algorithm(nullptr) {}
MazeSolution::MazeSolution(const Maze &m, Algorithm *alg) : maze(m), algorithm(alg) {}
void MazeSolution::display()
{
    std::cout << "Displaying maze solution..." << std::endl;
}