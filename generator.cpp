#include "generator.hpp"
#include "algorithm.hpp"
#include <string.h>
#include <iostream>
using namespace std;

float Maze2dGenerator::measureAlgorithmTime() {
    auto start = chrono::high_resolution_clock::now();
    generate(); 
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> duration = end - start;
    return duration.count();
}


    Maze SimpleMaze2dGenerator::generate(Maze maze, Algorithm algorithm) {
        // Implementation of the generate function using a specific algorithm
        // You should replace this with the actual implementation using the provided Maze and Algorithm parameters
        // ...

        return maze; // Return the generated Maze
    }

    void SimpleMaze2dGenerator::compress(Maze maze) {
        // Implementation of the compress function
        // You should replace this with the actual implementation using the provided Maze parameter
        // ...
    }