#include "system.hpp"
#include "generator.hpp"
#include <string.h>
#include <iostream>
#include <filesystem>
using namespace std;
namespace fs = std::filesystem;
std::chrono::high_resolution_clock::time_point startTimeS;
std::chrono::high_resolution_clock::time_point endTimeS;

GameSystem *GameSystem::game_instance = nullptr;

GameSystem::~GameSystem(){
    if(mySolutions)  delete mySolutions; 
    if(myMazes) delete myMazes; 
}

GameSystem::GameSystem()
{
    mySolutions = SolutionRepository::getInstance();
    myMazes = MazeRepository::getInstance();
}

GameSystem *GameSystem::getInstance()
{
    if (!game_instance)
    {
        game_instance = new GameSystem();
    }
    return game_instance;
}

void GameSystem::exit()
{
    delete game_instance;
    game_instance = nullptr;
}

void startTimerS()
{
    startTimeS = std::chrono::high_resolution_clock::now();
}

// Function to stop measuring time and print the elapsed time
void stopTimerS()
{
    endTimeS = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> elapsedTime = endTimeS - startTimeS;
    std::cout << "Algorithm took " << elapsedTime.count() << " seconds." << std::endl;
}

void GameSystem::gameStart()
{
    if (1)
    {
        int flagKeepPlay = 1;
        cout << "Game is starting..." << std::endl;
        currentState = PLAYING;
        do
        {
            this->currentMaze->display();
            cout << "what would you like to do? (0- UP | 1- Down | 2- Left | 3- Right | 4- Stop Play)" << endl;
            int inputCommand;
            cin >> inputCommand;
            switch (inputCommand)
            {
            case 0:
                toDo = Up;
                break;
            case 1:
                toDo = Down;
                break;
            case 2:
                toDo = Left;
                break;
            case 3:
                toDo = Right;
                break;
            case 4:
                flagKeepPlay = 0;
                break;
            default:
                cout << "Invalid command!\n";
            }
            if (inputCommand != 4)
            {
                execute(toDo, this->currentMaze);
            }
        } while (flagKeepPlay);
    }
}

void GameSystem::gameReset()
{
    if (currentState == PLAYING)
    {
        std::cout << "Resetting the game..." << std::endl;
        currentMaze->setUserPoint(currentMaze->getStartPoint()->getX(), currentMaze->getStartPoint()->getY());
    }
}

void GameSystem::saveMaze(Maze *maze)
{
    myMazes->saveMaze(maze);
}

void GameSystem::saveMazeExistF(Maze *maze)
{
    int whatFile;
    cout << "what file would you like to choose?" << endl;
    cin >> whatFile;
    myMazes->saveMazeExist(maze, whatFile);
}

Maze GameSystem::chooseMaze(const string &name)
{
    for (Maze maze : myMazes->getMazeList())
    {
        if (maze.getMazeName() == name)
        {
            return maze;
        }
    }
    cout << "maze wasn't found!";
    throw std::runtime_error("Maze not found.");
}

void GameSystem::listFiles()
{
    std::cout << "List of mazes in the repository:" << std::endl;
    for (Maze maze : myMazes->getMazeList())
    {
        std::cout << maze.getMazeName() << std::endl;
    }
}

void GameSystem::showMazes(int index)
{

    myMazes->showAllMazes(index);
}

Maze GameSystem::loadMyMaze(int index, string fileName)
{
    return myMazes->getMaze(index, fileName);
}

void GameSystem::listFilesInDirectory(const std::string &path)
{
    for (const auto &entry : std::filesystem::directory_iterator(path))
    {
        std::cout << entry.path() << std::endl;
    }
}

void GameSystem::getFileSize(const string &path)
{
    vector<string> fileList;
    int index = 1;

    for (const auto &entry : filesystem::directory_iterator(path))
    {
        fileList.push_back(entry.path().string());
        cout << index << "- " << entry.path().filename() << endl;
        index++;
    }

    if (!fileList.empty())
    {
        int choice;
        cout << "Choose a file by entering its index: ";
        cin >> choice;

        if (choice > 0 && choice <= fileList.size())
        {
            string selectedFilePath = fileList[choice - 1];
            filesystem::path selectedPath = selectedFilePath;

            if (filesystem::exists(selectedPath) && filesystem::is_regular_file(selectedPath))
            {
                uintmax_t fileSize = filesystem::file_size(selectedPath);
                cout << "File size of " << selectedPath.filename() << ": " << fileSize << " bytes" << endl;
            }
            else
            {
                cerr << "Invalid file selection." << endl;
            }
        }
        else
        {
            cerr << "Invalid choice." << endl;
        }
    }
    else
    {
        cout << "No files in the directory." << endl;
    }
}

void GameSystem::listTxtFilesInDirectory()
{
    cout << "Existing .txt files in the current directory:" << endl;

    vector<string> txtFiles;

    int index = 0;
    for (const auto &entry : fs::directory_iterator("."))
    {
        if (entry.path().extension() == ".txt" && entry.path().filename() != "solution.txt")
        {
            txtFiles.push_back(entry.path().filename());
            cout << index << ". " << entry.path().filename() << endl;
            index++;
        }
    }
    if (txtFiles.empty())
    {
        throw std::runtime_error("No .txt files found in the current directory.");
    }
}

void GameSystem::listTxtFilesInDirectory(vector<string> &txtFiles)
{

    txtFiles.clear();

    int index = 0;
    for (const auto &entry : fs::directory_iterator("."))
    {
        if (entry.path().extension() == ".txt")
        {
            txtFiles.push_back(entry.path().filename());
            index++;
        }
    }
    if (txtFiles.empty())
    {
        throw std::runtime_error("No .txt files found in the current directory.");
    }
}

Maze GameSystem::loadMyMazeFromRepository(int index)
{
    return myMazes->getMazeFromList(index);
}

string GameSystem::getFileNameByIndex(int index)
{
    vector<string> txtFiles;
    listTxtFilesInDirectory(txtFiles);

    if (index >= 0 && index < txtFiles.size())
    {
        return txtFiles[index];
    }
    else
    {
        throw std::out_of_range("Invalid index.");
    }
}


void GameSystem::compareAlgorithms(Algorithm* algorithm1, Algorithm* algorithm2){
    algorithm1->getAlgorithmNameOS(cout)<<" runtime:"<<endl;
    startTimerS();
    algorithm1->solveMaze(*this->currentMaze);
    stopTimerS();
    algorithm2->getAlgorithmNameOS(cout)<<" runtime:"<<endl;
    startTimerS();
    algorithm2->solveMaze(*this->currentMaze);
    stopTimerS();
}

