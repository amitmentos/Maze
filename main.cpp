#include "string.h"
#include <vector>
#include <filesystem>
#include "system.hpp"
#include "generator.hpp"
#include <iostream>
using namespace std;

//*************************************************************************************
// Amit Ronen Id: 205733975
// Ben Gurevich Id: 206904880
//**********************************************************************************
extern GameSystem *myGame;
int main()
{
    int select;
    int flag = 0;
    int flagNew = 0;
    int flagPlay = 1;
    int flagBack = 1;
    int whatMaze, whereToSave, whereToLoadFrom;
    GameSystem *myGame = GameSystem::getInstance();
    int whatSize, whatFile;
    string mazeName;
    SimpleMaze2dGenerator newMazegenerator;
    myMaze2dGenerator newAstargenerator;
    Maze changeMaze;
    std::filesystem::path currentPath = std::filesystem::current_path();

    cout << endl
         << endl;
    cout << "88,dPYba,,adPYba,  ,adPPYYba, 888888888  ,adPPYba,  \n";
    cout << "88P'   \"88\"    \"8a \"\"     `Y8      a8P\" a8P_____88  \n";
    cout << "88      88      88 ,adPPPPP88   ,d8P'   8PP\"\"\"\"\"\"\"  \n";
    cout << "88      88      88 88,    ,88 ,d8\"      \"8b,   ,aa  \n";
    cout << "88      88      88 `\"8bbdP\"Y8 888888888  `\"Ybbd8\"'   \n";

    while (true)
    {
        if (!flagPlay)
        {
            flag = 0;
        }
        do
        {
            cout << "----------------------------------------------------------------------------------------------------------" << endl;
            cout << "What would you like to do?" << endl; // first menu
            cout << "0- EXIT                        1-  Create Maze" << endl;
            cout << "2- Load Maze                   3-  List files" << endl;
            cout << "4- Get file size               5- List maze I created" << endl;
            cin >> select;
        } while (select < 0 || select > 5);

        switch (select)
        {
        case 0:
        {
            myGame->exit();
            return 0;
        }
        case 1:
        {
            cout << "What is the size of the maze you want to create?" << endl;
            cin >> whatSize;
            cout << "What is the name of the maze you want to create?" << endl;
            cin >> mazeName;
            Maze *newMaze = new Maze(newAstargenerator.generate(whatSize, mazeName));
            myGame->setCurrentMaze(newMaze);
            flag = 1;
            flagNew = 1;
            flagBack = 1;
            break;
        }
        case 2:
        {
            cout << "Would you like to load from a file or one that you created?(0-File | 1- Created)" << endl;
            cin >> whereToLoadFrom;
            if (!whereToLoadFrom)
            {
                myGame->listTxtFilesInDirectory();
                cout << "what file would you like to choose?" << endl;
                cin >> whatFile;
                myGame->showMazes(whatFile);
                cout << "What maze would you like to load?" << endl;
                cin >> whatMaze;
                Maze loadedMaze = myGame->loadMyMaze(whatMaze);
                myGame->setCurrentMaze(&loadedMaze);
            }
            else{
                myGame->showMyMazes();
                cout << "What maze would you like to load?" << endl;
                cin >> whatMaze;
                Maze loadedMaze2 = myGame->loadMyMazeFromRepository(whatMaze);
                myGame->setCurrentMaze(&loadedMaze2);
            }
            flag = 1;
            flagNew = 0;
            flagBack = 1;
            break;
        }
        case 3:
            int whatPath;
            cout << "Where do you want to list files from? (0- Current Path 1- Other)" << endl;
            cin >> whatPath;
            if (whatPath == 0)
            {
                myGame->listFilesInDirectory(currentPath.string());
            }
            if (whatPath == 1)
            {
                cout << "Please enter your path:" << endl;
                string path;
                cin >> path;

                try
                {
                    myGame->listFilesInDirectory(path);
                }
                catch (const std::filesystem::filesystem_error &e)
                {
                    cout << e.what() << endl;
                }
            }
            break;

        case 4:
            int whatPathSize;
            cout << "Where do you want to get size of the file from? (0- Current Path 1- Other)" << endl;
            cin >> whatPathSize;
            if (whatPathSize == 0)
            {
                myGame->getFileSize(currentPath.string());
            }
            if (whatPathSize == 1)
            {
                cout << "Please enter your path:" << endl;
                string path;
                cin >> path;

                try
                {
                    myGame->getFileSize(path);
                }
                catch (const std::filesystem::filesystem_error &e)
                {
                    cout << e.what() << endl;
                }
            }
        case 5:
            myGame->showMyMazes();
            break;

            // default:
            //     cout << "asd";
            //     break;
        }
        if (flag)
        {
            while (flagBack)
            {
                cout << "----------------------------------------------------------------------------------------------------------" << endl;
                cout << "What would you like to do?" << endl; // second menu
                cout << "0- Back                   1-  Save Maze" << endl;
                cout << "2- Play Maze              3-  Show Maze" << endl;
                cout << "4- Show solution          5-  Change Maze" << endl;
                cin >> select;
                switch (select)
                {
                case 0:
                    flagBack = 0;
                    break;

                case 1:
                    if (flagNew)
                    {
                        cout << "What do you want to save the maze to?(0- Choose TXT file | 1- create new file)" << endl;
                        cin >> whereToSave;
                        if (whereToSave)
                        {
                            myGame->saveMaze(myGame->getCurrentMaze());
                        }
                        else
                        {
                            myGame->listTxtFilesInDirectory();
                            myGame->saveMazeExistF(myGame->getCurrentMaze());
                        }
                        cout << "Current maze was saved successfully!!" << endl;
                        break;
                    }
                    else
                    {
                        cout << "Current maze is already in memory!!" << endl;
                    }
                    flagNew = 0;
                    break;

                case 2:
                    do
                    {
                        myGame->gameStart();
                        cout << "Would you like to keep playing? (0- No | 1- Yes)" << endl;
                        cin >> flagPlay;
                    } while (flagPlay);

                    break;

                case 3:
                    myGame->displayMaze(myGame->getCurrentMaze());
                    break;

                case 4:
                    myGame->getmySolutions()->showSolution(myGame->getCurrentMaze()->getMazeName());
                    break;

                case 5:
                    myGame->listTxtFilesInDirectory();
                    cout << "what file would you like to choose?" << endl;
                    cin >> whatFile;
                    myGame->showMazes(whatFile);
                    cout << "What maze would you like to change for?" << endl;
                    cin >> whatMaze;
                    changeMaze = myGame->loadMyMaze(whatMaze);
                    myGame->setCurrentMaze(&changeMaze);
                    break;

                default:
                    cout << "asd";
                    break;
                }
            }
        }
    }
}
