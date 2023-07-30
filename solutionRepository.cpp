#include "solutionRepository.hpp"
#include <string.h>
#include <iostream>
using namespace std;

SolutionRepository* SolutionRepository::_instance = nullptr;

SolutionRepository::SolutionRepository() {}

SolutionRepository* SolutionRepository::getInstance() {
    if (!_instance) {
        _instance = new SolutionRepository();
    }
    return _instance;
}

SolutionRepository::~SolutionRepository() {
    // Clean up the solutions map
    for (const auto& pair : solutions) {
        delete pair.second; // Delete mazeSolution objects
    }
    solutions.clear();
}

bool SolutionRepository::saveSolution(const string& mazeName, MazeSolution* toAdd) {
    // Check if the maze solution already exists in the repository
    if (solutions.find(mazeName) != solutions.end()) {
        std::cout << "Solution for maze '" << mazeName << "' already exists." << std::endl;
        return false;
    }

    // Add the solution to the repository
    solutions[mazeName] = toAdd;
    return true;
}

MazeSolution* SolutionRepository::getSolution(const std::string& name) {
    auto it = solutions.find(name);
    if (it != solutions.end()) {
        return it->second;
    }
    return nullptr; // Maze solution not found
}

void SolutionRepository::showSolution(const std::string& name) {
    auto it = solutions.find(name);
    if (it != solutions.end()) {
        // Display solution details (modify as per your mazeSolution class implementation)
        std::cout << "Solution for maze '" << name << "':" << std::endl;
        it->second->display(); // Assuming there's a showDetails() function in mazeSolution
    } else {
        std::cout << "Solution for maze '" << name << "' not found." << std::endl;
    }
}