#include "string.h"
#include <vector>
#include "system.hpp"
#include "generator.hpp"
#include <iostream>
using namespace std;

//*************************************************************************************
// Amit Ronen Id: 205733975
// Ben Gurevich Id: 206904880
//**********************************************************************************

int main()
{
    int select;
    int flag = 0;
    int flagNew = 0;
    int flagPlay = 1;
    int flagBack=1;
    int whatMaze;
    GameSystem *myGame = GameSystem::getInstance();
    int whatSize;
    string mazeName;
    SimpleMaze2dGenerator newMazegenerator;
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
            cin >> select;
        } while (select < 0 || select > 3);

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
            Maze *newMaze = new Maze(newMazegenerator.generate(whatSize, mazeName));
            myGame->setCurrentMaze(newMaze);
            flag = 1;
            flagNew = 1;
            flagBack = 1;
            break;
        }
        case 2:
        {
            myGame->showMazes();
            cout << "What maze would you like to load?" << endl;
            cin >> whatMaze;
            Maze *loadedMaze = myGame->loadMyMaze(whatMaze);
            if (loadedMaze != nullptr)
            {
                myGame->setCurrentMaze(loadedMaze);
            }
            else
            {
                cout << "Error: Maze not found." << endl;
            }
            flagNew = 0;
            break;
        }
            // case 3:
            //     cout << "asd";
            //     break;

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
                cout << "4- Show solution                       " << endl;
                cin >> select;
                switch (select)
                {
                case 0:
                    flagBack = 0;
                    break;

                case 1:
                    if (flagNew)
                    {
                        myGame->saveMaze(myGame->getCurrentMaze());
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

                    // default:
                    //     cout << "asd";
                    //     break;
                }
            }
        }
    }
}
