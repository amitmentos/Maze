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
//!!Workspace!!
//     Macbook pro- macOS 13.5
//     g++:
//      (Homebrew GCC 12.2.0) 12.2.0
//     clang:
//      Apple clang version 14.0.3 (clang-1403.0.22.14.1)

extern GameSystem *myGame;
int main()
{
    int select;
    int flag = 0;
    int flagNew = 0;
    int flagPlay = 1;
    int flagBack = 1;
    int flagErrorL = 1;
    int whatMaze, whereToSave, whereToLoadFrom, WhatAlgorithm, compare1, compare2;
    GameSystem *myGame = GameSystem::getInstance();
    int whatSize, whatFile;
    string mazeName;
    SimpleMaze2dGenerator newMazegenerator;
    myMaze2dGenerator newPrimgenerator;
    Maze changeMaze;
    bool loadedSuccessfully = false;
    bool loadFileSucc = false;
    bool loadFileSucc2 = false;
    AlgorithmList algorithmList;
    BFS *bfs = new BFS;
    AStar *astar = new AStar;
    Prim *prim = new Prim;
    algorithmList.addAlgorithm(bfs);
    algorithmList.addAlgorithm(astar);
    algorithmList.addAlgorithm(prim);
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
            cout << "4- Get file size               5-  List maze I created" << endl;
            cin >> select;
        } while (select < 0 || select > 5);
        loadedSuccessfully = false;
        loadFileSucc = false;
        loadFileSucc2 = false;
        switch (select)
        {
        case 0:
        {
            myGame->exit();
            delete bfs;
            delete prim;
            delete astar;
            return 0;
        }
        case 1:
        {
            cout << "What algorithm do you want to use to create the maze?(0- Random | 1- Prim)" << endl;
            cin >> WhatAlgorithm;
            cout << "What is the size of the maze you want to create?" << endl;
            cin >> whatSize;
            cout << "What is the name of the maze you want to create?" << endl;
            cin >> mazeName;
            if (!WhatAlgorithm)
            {
                Maze *newMaze = new Maze(newMazegenerator.generate(whatSize, mazeName));
                myGame->setCurrentMaze(newMaze);
            }
            else
            {
                if(WhatAlgorithm!= 1){cout<<"invaild input! it created the maze with defult algorithm- Prim"<<endl;}
                Maze *newMaze = new Maze(newPrimgenerator.generate(whatSize, mazeName));
                myGame->setCurrentMaze(newMaze);
            }
            flag = 1;
            flagNew = 1;
            flagBack = 1;
            break;
        }
        case 2:
        {
            do
            {
                cout << "Would you like to load from a file or one that you created? (0-File | 1-Created | 2- Back)" << endl;
                cin >> whereToLoadFrom;

                try
                {
                    if (whereToLoadFrom == 0)
                    {
                        do
                        {
                            try
                            {
                                myGame->listTxtFilesInDirectory();
                                cout << "What file would you like to choose?" << endl;
                                cin >> whatFile;
                                myGame->showMazes(whatFile);
                                cout << "What maze would you like to load?" << endl;
                                cin >> whatMaze;
                                loadFileSucc2 = true;
                                flagErrorL = 1;
                            }
                            catch (const std::exception &ex)
                            {
                                cout << "An exception occurred: " << ex.what() << endl;
                            }
                        } while (!loadFileSucc2);
                        Maze loadedMaze = myGame->loadMyMaze(whatMaze, myGame->getFileNameByIndex(whatFile));
                        myGame->setCurrentMaze(&loadedMaze);
                    }
                    if (whereToLoadFrom == 1)
                    {
                        do
                        {
                            try
                            {
                                myGame->showMyMazes();
                                cout << "What maze would you like to load?" << endl;
                                cin >> whatMaze;
                                Maze loadedMaze2 = myGame->loadMyMazeFromRepository(whatMaze);
                                myGame->setCurrentMaze(&loadedMaze2);
                                loadFileSucc2 = true;
                                flagErrorL = 1;
                            }
                            catch (const std::exception &ex)
                            {
                                cout << "An exception occurred: " << ex.what() << endl;
                                loadFileSucc2 = true;
                                flagErrorL = 0;
                                
                            }
                        } while (!loadFileSucc2);
                    }
                    if (whereToLoadFrom == 2)
                        break;
                    // No exceptions were thrown, so set e to false to exit the loop
                    if(flagErrorL){
                    loadedSuccessfully = true;
                    flag = 1;
                    flagNew = 0;
                    flagBack = 1;
                    }
                }
                catch (const std::exception &ex)
                {
                    // Handle the exception (print error message, etc.)
                    cout << "An exception occurred: " << ex.what() << endl;
                }
            } while (!loadedSuccessfully);
            break;
        }
        case 3:
            int whatPath;
            cout << "Where do you want to list files from? (0- Current Path | 1- Other)" << endl;
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
                    cin.ignore();
                }
            }
            if(whatPath!=0 && whatPath!= 1){cout<<"Invaild input!"<<endl;}
            break;

        case 4:
            int whatPathSize;
            cout << "Where do you want to get size of the file from? (0- Current Path | 1- Other)" << endl;
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
            if(whatPath!=0 && whatPath!= 1){cout<<"Invaild input!"<<endl;}
            break;

        case 5:
            try
            {
                myGame->showMyMazes();
                break;
            }
            catch (const exception &ex)
            {
                cout << "An exception occurred: " << ex.what() << endl;
            }
            break;

        default:
            cout << "Please try again" << endl;
            break;
        }
        if (flag)
        {
            while (flagBack)
            {
                do
                {
                    cout << "----------------------------------------------------------------------------------------------------------" << endl;
                    cout << "What would you like to do?" << endl; // second menu
                    cout << "0- Back                   1-  Save Maze" << endl;
                    cout << "2- Play Maze              3-  Show Maze" << endl;
                    cout << "4- Show solution          5-  Change Maze" << endl;
                    cout << "6- Test algorithms        7-  Get maze data" << endl;
                    cin >> select;
                    loadedSuccessfully = false;
                    loadFileSucc = false;
                } while (select < 0 || select > 7);
                switch (select)
                {
                case 0:
                    flagBack = 0;
                    break;

                case 1:
                    if (flagNew)
                    {
                        cout << "Where do you want to save the maze to?(0- Choose TXT file | 1- create new file)" << endl;
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
                        myGame->getmySolutions()->savePathFile(*myGame->getmySolutions()->getSolution(myGame->getCurrentMaze()->getMazeName()));
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
                    do
                    {
                        cout << "Would you like to load from a file or one that you created? (0-File | 1-Created | 2- Back)" << endl;
                        cin >> whereToLoadFrom;

                        try
                        {
                            if (whereToLoadFrom == 0)
                            {
                                do
                                {
                                    try
                                    {
                                        myGame->listTxtFilesInDirectory();
                                        cout << "What file would you like to choose?" << endl;
                                        cin >> whatFile;
                                        myGame->showMazes(whatFile);
                                        cout << "What maze would you like to load?" << endl;
                                        cin >> whatMaze;
                                        loadFileSucc = true;
                                    }
                                    catch (const std::exception &ex)
                                    {
                                        cout << "An exception occurred: " << ex.what() << endl;
                                    }
                                } while (!loadFileSucc);
                                Maze loadedMaze = myGame->loadMyMaze(whatMaze, myGame->getFileNameByIndex(whatFile));
                                myGame->setCurrentMaze(&loadedMaze);
                                loadedSuccessfully = true;
                            }
                            if (whereToLoadFrom == 1)
                            {
                                do
                                {
                                    try
                                    {
                                        myGame->showMyMazes();
                                        cout << "What maze would you like to load?" << endl;
                                        cin >> whatMaze;
                                        Maze loadedMaze2 = myGame->loadMyMazeFromRepository(whatMaze);
                                        myGame->setCurrentMaze(&loadedMaze2);
                                        loadFileSucc = true;
                                    }
                                    catch (const std::exception &ex)
                                    {
                                        cout << "An exception occurred: " << ex.what() << endl;
                                    }
                                } while (!loadFileSucc);
                                loadedSuccessfully = true;
                            }
                            if (whereToLoadFrom == 2)
                            {
                                loadedSuccessfully = true;
                            }
                        }
                        catch (const std::exception &ex)
                        {
                            cout << "An exception occurred: " << ex.what() << endl;
                        }
                    } while (!loadedSuccessfully);
                    break;

                case 6:
                    do{
                        cout << "Please choose the first algorith: (0- BFS | 1- A* | 2- Prim)" << endl;
                        cin >> compare1;
                    }while(compare1<0 || compare1>2);
                    do{
                        cout << "Please choose the second algorith: (0- BFS | 1- A* | 2- Prim)" << endl;
                        cin >> compare2;
                    }while(compare2<0 || compare2>2);
                    myGame->compareAlgorithms(algorithmList.getAlgorithm(compare1), algorithmList.getAlgorithm(compare2));
                    break;

                case 7:
                    myGame->getCurrentMazeData();
                    break;

                default:
                    cout << "Please try again" << endl;
                    break;
                }
            }
        }
    }
}
