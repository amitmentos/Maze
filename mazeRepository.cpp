#include "mazeRepository.hpp"
#include "maze.hpp"
#include "generator.hpp"
#include "system.hpp"
#include <string.h>
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;



MazeRepository *MazeRepository::maze_instance = nullptr;

MazeRepository::MazeRepository() {}

bool isFileEmpty(const std::string& fileName) {
    std::ifstream file(fileName);
    return file.peek() == std::ifstream::traits_type::eof();
}

MazeRepository *MazeRepository::getInstance()
{
    if (!maze_instance)
    {
        maze_instance = new MazeRepository();
    }
    return maze_instance;
}

MazeRepository::~MazeRepository()
{
}

void MazeRepository::saveMaze(Maze *toAdd)
{
    MazeCompressor compressor;
    vector<string> compressedMaze = compressor.compress(*toAdd);
    cout << "Maze Name: " << compressedMaze[0] << endl;
    cout << "Compressed Maze: " << compressedMaze[1] << endl;
    compressor.writeStringToFile(compressedMaze);
    // mazeList.push_back(toAdd);
}

void MazeRepository::saveMazeExist(Maze *toAdd, int index)
{
    MazeCompressor compressor;
    vector<string> compressedMaze = compressor.compress(*toAdd);
    cout << "Maze Name: " << compressedMaze[0] << endl;
    cout << "Compressed Maze: " << compressedMaze[1] << endl;
    compressor.appendContentToFile(compressedMaze, index);
    // mazeList.push_back(toAdd);
}


Maze MazeRepository::getMaze(const string &name)
{
    for (Maze maze : mazeList)
    {
        if (maze.getMazeName() == name)
        {
            return maze;
        }
    }
    throw std::runtime_error("Maze not found.");
}

void MazeRepository::showMaze(const std::string &name)
{
    for (Maze maze : mazeList)
    {
        if (maze.getMazeName() == name)
        {
            // Display maze details (modify as per your Maze class implementation)
            std::cout << "Maze Name: " << maze.getMazeName() << std::endl;
            std::cout << "Maze Size: " << maze.getSize() << std::endl;
            // Add more details specific to your Maze class
            return;
        }
    }
    std::cout << "Maze not found." << std::endl;
}

bool MazeRepository::showAllMazes(int fileIndex)
{
    vector<string> txtFiles;
    GameSystem *myGame = GameSystem::getInstance();
    myGame->listTxtFilesInDirectory(txtFiles);
    if (isFileEmpty(txtFiles[fileIndex]))
    {
        throw std::runtime_error("Invaild value.");
    }
    if (fileIndex >= 0 && fileIndex < txtFiles.size() && txtFiles[fileIndex] != "solution.txt") {
        string chosenFile = txtFiles[fileIndex];
        ifstream file(chosenFile);
        if (!file.is_open()) {
            cerr << "Error: Unable to open file." << endl;
            return false;
        }

        cout << "All mazes in the selected file:" << endl;

        string line;
        int index = 0;
        while (getline(file, line))
        {
            istringstream iss(line);
            string mazeName, compressed;
            if (getline(iss, mazeName, ','))
            {
                cout << index << ". " << mazeName << endl;
                index++;
            }
        }

        file.close();
        return true;
    } else {
        cerr << "Invalid file index." << endl;
        return false;
    }
}

Maze MazeRepository::getMaze(int index, string fileName)
{
    
    MazeCompressor compressor;
    GameSystem *myGame = GameSystem::getInstance();
    MazeSolution mySolution;
    Maze myMaze = compressor.decompress(fileName,index);
    mySolution = compressor.decompressPath(myMaze.getMazeName());

    myGame->getmySolutions()->saveSolution(mySolution.getMazeName(),mySolution);
    return myMaze;
}

void MazeRepository::saveMazeToRepository(Maze toAdd) {
    // Check if a maze with the same name already exists in the repository
    for (Maze maze : mazeList) {
        if (maze.getMazeName() == toAdd.getMazeName()) {
            std::cout << "Maze with name '" << toAdd.getMazeName() << "' already exists in the repository." << std::endl;
            return;  // Maze with the same name found, no need to add
        }
    }
    mazeList.push_back(toAdd);
}


void MazeRepository::showMazeList()
{
    if (mazeList.empty())
    {
        cout << "No mazes in the repository." << endl;
        throw std::runtime_error("no mazes");
        return;
    }

    cout << "All mazes in the repository:" << endl;

    for (size_t i = 0; i < mazeList.size(); i++)
    {
        cout << i << ". " << mazeList[i].getMazeName() << endl;
    }
}





