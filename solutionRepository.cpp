#include "solutionRepository.hpp"
#include <string.h>
#include <iostream>
using namespace std;

SolutionRepository* SolutionRepository::solution_instance = nullptr;

SolutionRepository::SolutionRepository() {}

SolutionRepository* SolutionRepository::getInstance() {
    if (!solution_instance) {
        solution_instance = new SolutionRepository();
    }
    return solution_instance;
}

SolutionRepository::~SolutionRepository() {
    solutions.clear();
}

bool SolutionRepository::saveSolution(const string& mazeName, MazeSolution toAdd) {
    if (solutions.find(mazeName) != solutions.end()) {
        std::cout << "Solution for maze '" << mazeName << "' already exists." << std::endl;
        return false;
    }
    solutions[mazeName] = toAdd;
    return true;
}

MazeSolution* SolutionRepository::getSolution(const string& name) {
    auto it = solutions.find(name);
    if (it != solutions.end()) {
        return &it->second;
    }
    return nullptr; // Maze solution not found
}

void SolutionRepository::showSolution(const string& name) {
    auto it = solutions.find(name);
    if (it != solutions.end()) {
        // Display solution details (modify as per your mazeSolution class implementation)
        cout << "Solution for maze '" << name << "':" << endl;
        it->second.display(); // Assuming there's a showDetails() function in mazeSolution
    } else {
        cout << "Solution for maze '" << name << "' not found." << endl;
    }
}