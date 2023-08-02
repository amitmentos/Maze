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
    for (const auto& pair : solutions) {
        delete pair.second; 
    }
    solutions.clear();
}

bool SolutionRepository::saveSolution(const string& mazeName, MazeSolution* toAdd) {
    if (solutions.find(mazeName) != solutions.end()) {
        std::cout << "Solution for maze '" << mazeName << "' already exists." << std::endl;
        return false;
    }

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