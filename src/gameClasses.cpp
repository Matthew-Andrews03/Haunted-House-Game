
#define MAP_SIZE 25
#include "gameClasses.h"
#include <random>
#include <ctime>
using namespace std;

// Class member function implementations
player::player() {}
player::player(string initname, int initscore, string initmini, string initskin)
{
    playerName = initname;
    score = initscore;
    skin = initskin;
    hasKey1 = false;
    hasKey2 = false;
}

string player::getName()
{
    return playerName; // Return playerName member variable
}

void player::setName(string namein)
{
    playerName = namein;
}

int player::getScore()
{
    return score;
}

void player::setScore(int score)
{
    score = score;
}

void player::resetScore()
{
    score = 0;
}

string player::getMiniToBeat()
{
    return miniToBeat;
}

void player::setMiniToBeat(string miniin)
{
    miniToBeat = miniin;
}

string player::getSkinRight()
{
    return "resources/" + skin + "2.png";
}

string player::getSkinLeft()
{
    return "resources/" + skin + "1.png";
}

void player::setSkin(string skinin)
{
    skin = skinin;
}

game::game() {}
game::game(player initplayer, room initrooms[MAP_SIZE][MAP_SIZE], int initcurrentindex, int initdifficulty, string initscreen) {}

int game::startGame() {}
void game::update() {}
void game::display() {}

int game::getDifficulty() {}
void game::setDifficulty(int difficultyin) {}

string game::getCurrentScreen() {}
void game::setCurrentScreen(string screenin) {}

room::room() {}
room::room(string inittype, bool isGhosttoRight, bool isGhosttoLeft, bool isGhostAbove, bool isGhostBelow) {}
void room::setRoomType(string typein) {}
bool room::getIsGhostInRoom() {}
void room::setIsGhostInRoom(bool isGhostinRoom) {}

void room::setGhostLocation(string doorToLock)
{

    if (doorToLock == "top")
        this->isGhostAbove = true;

    if (doorToLock == "bottom")
        this->isGhostBelow = true;

    if (doorToLock == "left")
        this->isGhosttoLeft = true;

    if (doorToLock == "right")
        this->isGhosttoRight = true;
}

void room::resetGhostLocations()
{
    this->isGhostAbove = false;
    this->isGhostBelow = false;
    this->isGhosttoLeft = false;
    this->isGhosttoRight = false;
}

void room::getRoom(int arr[][12], bool finalDoor)
{
    for (int i = 0; i < 12; i++)
    {
        if (i <= 1)
        {
            for (int j = 0; j < 13; j++)
            {
                arr[j][i] = 1;
            }
        }
        else if (i >= 10)
        {
            for (int j = 0; j < 13; j++)
            {
                arr[j][i] = 1;
            }
        }
        else
        {
            arr[0][i] = 1;
            arr[12][i] = 1;
        }
    }
    if (this->roomType == "centre")
    {
        
        if (this->isGhosttoLeft)
            arr[0][5] = 3; // Locked Left
        else
            arr[0][5] = 2; // Left

        if (this->isGhosttoRight)
            arr[12][5] = 3; // Locked Right
        else
            arr[12][5] = 2; // Right

        if (this->isGhostAbove)
            arr[6][0] = 3; // Locked Top
        else
            arr[6][0] = 2; // Top

        if (this->isGhostBelow)
            arr[6][10] = 3; // Locked bottom
        else
            arr[6][10] = 2; // bottom
    }
    else if (this->roomType == "topLeft")
    {

        // Put in doors

        if (this->isGhosttoRight)
            arr[12][5] = 3; // Locked Right
        else
            arr[12][5] = 2; // Right

        if (this->isGhostBelow)
            arr[6][10] = 3; // Locked bottom
        else
            arr[6][10] = 2; // bottom
    }
    else if (this->roomType == "topRight")
    {

        // Put in doors
        if (this->isGhosttoLeft)
            arr[0][5] = 3; // Locked Left
        else
            arr[0][5] = 2; // Left

        if (this->isGhostBelow)
            arr[6][10] = 3; // Locked bottom
        else
            arr[6][10] = 2; // bottom
    }
    else if (this->roomType == "top")
    {

        // Put in doors
        if (this->isGhosttoLeft)
            arr[0][5] = 3; // Locked Left
        else
            arr[0][5] = 2; // Left

        if (this->isGhosttoRight)
            arr[12][5] = 3; // Locked Right
        else
            arr[12][5] = 2; // Right

        if (this->isGhostBelow)
            arr[6][10] = 3; // Locked bottom
        else
            arr[6][10] = 2; // bottom
    }
    else if (this->roomType == "left")
    {

        // Put in doors

        if (this->isGhosttoRight)
            arr[12][5] = 3; // Locked Right
        else
            arr[12][5] = 2; // Right

        if (this->isGhostAbove)
            arr[6][0] = 3; // Locked Top
        else
            arr[6][0] = 2; // Top

        if (this->isGhostBelow)
            arr[6][10] = 3; // Locked bottom
        else
            arr[6][10] = 2; // bottom
    }
    else if (this->roomType == "right")
    {

        // Put in doors
        if (this->isGhosttoLeft)
            arr[0][5] = 3; // Locked Left
        else
            arr[0][5] = 2; // Left

        if (this->isGhostAbove)
            arr[6][0] = 3; // Locked Top
        else
            arr[6][0] = 2; // Top

        if (this->isGhostBelow)
            arr[6][10] = 3; // Locked bottom
        else
            arr[6][10] = 2; // bottom
    }
    else if (this->roomType == "botLeft")
    {

        // Put in doors

        if (this->isGhosttoRight)
            arr[12][5] = 3; // Locked Right
        else
            arr[12][5] = 2; // Right

        if (this->isGhostAbove)
            arr[6][0] = 3; // Locked Top
        else
            arr[6][0] = 2; // Top
    }
    else if (this->roomType == "botRight")
    {

        // Put in doors
        if (this->isGhosttoLeft)
            arr[0][5] = 3; // Locked Left
        else
            arr[0][5] = 2; // Left

        if (this->isGhostAbove)
            arr[6][0] = 3; // Locked Top
        else
            arr[6][0] = 2; // Top

        if(finalDoor == false)
            arr[12][5] = 4; // Exit Door
        else
            arr[12][5] = 0;
            arr[12][6] = 0;
    }
    else if (this->roomType == "bot")
    {

        // Put in doors
        if (this->isGhosttoLeft)
            arr[0][5] = 3; // Locked Left
        else
            arr[0][5] = 2; // Left

        if (this->isGhosttoRight)
            arr[12][5] = 3; // Locked Right
        else
            arr[12][5] = 2; // Right

        if (this->isGhostAbove)
            arr[6][0] = 3; // Locked Top
        else
            arr[6][0] = 2; // Top
    }

    // if(this->isGhosttoLeft) printf("Ghost is to left\n");
    // if(this->isGhosttoRight) printf("Ghost is to right\n");
    // if(this->isGhostAbove) printf("Ghost is above\n");
    // if(this->isGhostBelow) printf("Ghost is below\n");
}

// Places two ghosts in different rooms, not in the room that the player spawns in (top left)
void game::placeGhostsInRoom(int ghostArray[3][3])
{

    srand((unsigned)time(0));

    int i = (rand() % 3);
    int j = (rand() % 3);

    while ((i == 0) && (j == 0))
    {
        i = (rand() % 3);
        j = (rand() % 3);
    }

    int x = (rand() % 3);
    int y = (rand() % 3);

    while (((x == i) && (y == j)) || ((x == 0) && (y == 0)))
    {
        x = (rand() % 3);
        y = (rand() % 3);
    }

    // printf("placing ghost in %d %d\n", i, j);
    ghostArray[i][j] = 1;

    // printf("placing ghost in %d %d\n", x, y);
    ghostArray[x][y] = 1;
}
// finds the coordinates of the ghost furthest from the start point
int game::findGhost(int ghostArray[3][3], int &ghostX, int &ghostY)
{
    int count = 0;
    for (int k = 2; k >= 0; k = k - 1)
    {
        for (int i = 2; i >= 0; i = i - 1)
        {
            if (ghostArray[k][i] == 1)
            {
                ghostX = k;
                ghostY = i;
                return 1;
            }
        }
    }
    return 0;
}
