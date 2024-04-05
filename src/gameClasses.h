#include <stdio.h>
#include <string>
#include "raylib.h"
#define MAP_SIZE 25

using namespace std;

class player
{

public:
    player();
    player(string initname, int initscore, string initmini, string initskin);

    string getName();
    void setName(string namein);

    int getScore();
    void setScore(int score);
    void resetScore();

    string getMiniToBeat();
    void setMiniToBeat(string miniin);

    string getSkinRight();
    string getSkinLeft();
    void setSkin(string skinin);

private:
    string playerName;
    int score;
    string miniToBeat;
    string skin;
    bool hasKey1;
    bool hasKey2;
};

class room
{

public:
    room();
    room(string inittype, bool isGhosttoRight, bool isGhosttoLeft, bool isGhostAbove, bool isGhostBelow);
    void getRoom(int arr[][12], bool finalDoor);
    string getRoomType();
    void setRoomType(string typein);
    bool getIsGhostInRoom();
    void setIsGhostInRoom(bool isGhostinRoom);
    void setGhostLocation(string doorToLock);
    void resetGhostLocations();

    string roomType;
    bool isGhosttoRight;
    bool isGhosttoLeft;
    bool isGhostAbove;
    bool isGhostBelow;
};

class game
{

public:
    game();
    game(player initplayer, room initrooms[MAP_SIZE][MAP_SIZE], int initcurrentindex, int initdifficulty, string initscreen);

    int startGame();
    void update();
    void display();

    int getDifficulty();
    void setDifficulty(int difficultyin);

    string getCurrentScreen();
    void setCurrentScreen(string screenin);
    void placeGhostsInRoom(int ghostArray[3][3]);
    int findGhost(int ghostArray[3][3], int &ghostX, int &ghostY);
    void setGhostLocation(string doorToLock);

private:
    player Player;
    room Rooms[MAP_SIZE][MAP_SIZE];
    int currentRoomIndex;
    int difficulty;
    string currentScreen;
};
