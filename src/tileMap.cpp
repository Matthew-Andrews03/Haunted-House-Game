#include "raylib.h"
#include "gameClasses.h"
#include "title.h"
//#include "minimap.h"
#include <math.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <cstdlib>
#include <filesystem>
#include <direct.h>

using namespace std;
int playerSize = 40;
int playerSpeed = 150;
int screenWidth = 520;
int screenHeight = 480;
int gameCount = 0;
int key = 0;
int playerScore = 1022;
bool finalDoor = false;
double startTime = -1;
int tileMap[12][12] = {};
int main(void)
{
    InitWindow(screenWidth, screenHeight, "Haunted House");
    float x = 100, y = 100; // base
    loadTitle();
    int model = getCharNum();
    string model_name;
    string player_name = loadName();

    // Player selection switch case
    switch (model)
    {
    case (1):
        model_name = "male";
        break;
    case (2):
        model_name = "female";
        break;
    case (3):
        model_name = "neutral";
        break;
    }

    // Player Info
    player player1(player_name, playerScore, "", model_name);

    // Room Textures
    Texture2D floor = LoadTexture("resources/floor.png");
    Texture2D wall = LoadTexture("resources/wall.png");
    Texture2D door = LoadTexture("resources/door.png");
    Texture2D table = LoadTexture("resources/table.png");
    Texture2D stool = LoadTexture("resources/stool.png");
    Texture2D plant1 = LoadTexture("resources/plant1.png");
    Texture2D plant2 = LoadTexture("resources/plant2.png");

    // Player Model textures
    Texture2D playerModelLeft = LoadTexture(player1.getSkinLeft().c_str());
    Texture2D playerModelRight = LoadTexture(player1.getSkinRight().c_str());
    Texture2D playerModel = playerModelRight;

    // Ghost texture
    Texture2D ghost = LoadTexture("resources/ghost1.png");

    // Vector to hold player position
    Vector2 playerPos;

    // set player spawn location
    playerPos.x = x;
    playerPos.y = y;

    // set ghost spawn location
    Vector2 ghostPos;
    ghostPos.x = 240;
    ghostPos.y = 200;

    // Strings of different room types at different locations (Change as we develop)
    string roomMap[3][3] = {{"topLeft", "top", "topRight"}, {"left", "centre", "right"}, {"botLeft", "bot", "botRight"}};

    // Indices for room navigation
    int currRoomX = 0;
    int currRoomY = 0;

    // Place ghosts in rooms
    game Game;
    int ghostArray[3][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
    Game.placeGhostsInRoom(ghostArray);

    for (int k = 2; k >= 0; k = k - 1)
    {
        for (int i = 2; i >= 0; i = i - 1)
        {
            if (ghostArray[k][i] == 1)
                printf("GHOST ARRAY: ghost at: %d %d\n", k, i);
        }
    }

    // coordinates to keep track of ghost on map
    int ghostX = 0;
    int ghostY = 0;

    Game.findGhost(ghostArray, ghostX, ghostY);
    printf("FIND GHOST: furthest ghost at %d %d\n", ghostX, ghostY);

    // A room variable to keep track of current room
    room currRoom;

    //Minimap mini(520, 480);

    while (!WindowShouldClose())
    {

        
        BeginDrawing();
        ClearBackground(GRAY);

        for (int k = 0; k < 13; k = k + 1)
        {
            for (int i = 0; i < 12; i = i + 1)
            {
                tileMap[k][i] = 0;
            }
        }

        \

        // Find which room to draw
        currRoom.roomType = roomMap[currRoomX][currRoomY];

        // lock corresponding door:

        //(CRX+1, CRY): top door
        if (currRoomX == ghostX + 1 && currRoomY == ghostY)
            currRoom.setGhostLocation("top");

        //(CRX, CRY-1): right door
        if (currRoomX == ghostX && currRoomY == ghostY - 1)
            currRoom.setGhostLocation("right");

        //(CRX, CRY+1): left door

        if (currRoomX == ghostX && currRoomY == ghostY + 1)
            currRoom.setGhostLocation("left");

        //(CRX-1, CRY): bottom door
        if (currRoomX == ghostX - 1 && currRoomY == ghostY)
            currRoom.setGhostLocation("bottom");

        currRoom.getRoom(tileMap, finalDoor);

        // Draw Room
        for (int k = 0; k < 13; k = k + 1)
        {
            for (int i = 0; i < 12; i = i + 1)
            {
                Vector2 pos;
                pos.x = k * playerSize;
                pos.y = i * playerSize;
                if (tileMap[k][i] == 0)
                    DrawTextureEx(floor, pos, 0, 2.5, WHITE);
                if (tileMap[k][i] == 1)
                    DrawTextureEx(wall, pos, 0, 2.5, WHITE);
                if (tileMap[k][i] == 2 && tileMap[k][i - 1] != 2)
                {
                    DrawTextureEx(door, pos, 0, 2.5, WHITE);
                    tileMap[k][i + 1] = 2;
                }
                if (tileMap[k][i] == 3 && tileMap[k][i - 1] != 3)
                {
                    DrawTextureEx(door, pos, 0, 2.5, WHITE);
                    tileMap[k][i + 1] = 3;
                }
                if (tileMap[k][i] == 4 && tileMap[k][i - 1] != 4)
                {
                    DrawTextureEx(door, pos, 0, 2.5, WHITE);
                    tileMap[k][i + 1] = 4;
                }
                if(tileMap[k][i] == 5){
                    DrawTextureEx(table, pos, 0, 2.5, WHITE);
                }
                if(tileMap[k][i] == 6){
                    DrawTextureEx(stool, pos, 0, 2.5, WHITE);
                }
                if(tileMap[k][i] == 7){
                    DrawTextureEx(plant1, pos, 0, 2.5, WHITE);
                }
                if(tileMap[k][i] == 8){
                    DrawTextureEx(plant2, pos, 0, 2.5, WHITE);
                }
            }
        }

        //mini.miniDraw(playerPos, currRoomX, currRoomY);
        if (IsKeyDown(KEY_W) || IsKeyDown(KEY_S) || IsKeyDown(KEY_A) || IsKeyDown(KEY_D))
        {
            if (startTime == -1) // Start the timer when the player first moves
            {
                startTime = GetTime();
            }
        }

        if (startTime != -1)
        {
        double elapsedTime = GetTime() - startTime;
        DrawText(TextFormat("Time: %.2f", elapsedTime), screenWidth - 120, 30, 20, WHITE);
        }

        // Update player position based on WASD inputs while checking for locked doors and walls
        if (IsKeyDown(KEY_W))
        {
            if (tileMap[(int)((playerPos.x + 30) / playerSize)][(int)((playerPos.y + 80) / playerSize) - 1] != 1 
            && tileMap[(int)((playerPos.x + 30) / playerSize)][(int)((playerPos.y + 80) / playerSize) - 1] != 3
            && tileMap[(int)((playerPos.x + 30) / playerSize)][(int)((playerPos.y + 80) / playerSize) - 1] != 4)
            y -= GetFrameTime() * playerSpeed;

        }

        if (IsKeyDown(KEY_S))
        {
            if (tileMap[(int)((playerPos.x + 30) / playerSize)][(int)((playerPos.y + 25) / playerSize) + 1] != 1 
            && tileMap[(int)((playerPos.x + 30) / playerSize)][(int)((playerPos.y + 25) / playerSize) + 1] != 3
            && tileMap[(int)((playerPos.x + 30) / playerSize)][(int)((playerPos.y + 25) / playerSize) + 1] != 3)
                y += GetFrameTime() * playerSpeed;

        }

        if (IsKeyDown(KEY_D))
        {
            if (tileMap[(int)((playerPos.x + 5) / playerSize) + 1][(int)((playerPos.y + 55) / playerSize)] != 1 
            && tileMap[(int)((playerPos.x + 5) / playerSize) + 1][(int)((playerPos.y + 55) / playerSize)] != 3
            && tileMap[(int)((playerPos.x + 5) / playerSize) + 1][(int)((playerPos.y + 55) / playerSize)] != 4)
                x += GetFrameTime() * playerSpeed;
            playerModel = playerModelRight;

        }

        if (IsKeyDown(KEY_A))
        {
            if (tileMap[(int)((playerPos.x + 10) / playerSize)][(int)((playerPos.y + 55) / playerSize)] != 1 
            && tileMap[(int)((playerPos.x + 10) / playerSize)][(int)((playerPos.y + 55) / playerSize)] != 3
            && tileMap[(int)((playerPos.x + 10) / playerSize)][(int)((playerPos.y + 55) / playerSize)] != 4)
                x -= GetFrameTime() * playerSpeed;
            playerModel = playerModelLeft;

        }

        // Draw the ghost in the current room if applicable
        if (ghostArray[currRoomX][currRoomY] == 1)
        {

            // printf("placing a ghost in room %d %d because ghost array equals %d\n", currRoomX, currRoomY, ghostArray[currRoomX][currRoomY]);
            DrawTextureEx(ghost, ghostPos, 0, 2.5, WHITE);

            if (playerPos.x > ghostPos.x - 60 && playerPos.x < ghostPos.x + 60 && playerPos.y > ghostPos.y - 60 && playerPos.y < ghostPos.y + 60)
            {
                DrawText(TextFormat("Press E to play Mini Game"), (screenWidth - 150) / 2, screenHeight - 100, 20, WHITE);
                if (gameCount == 0 && IsKeyPressed(KEY_E))
                {
                    // Command to execute the other executable
                    std::string pathToExecutable = "minigames\\pong\\pong_easy.exe";

                    // Start the executable
                    int result = std::system(pathToExecutable.c_str());

                    gameCount++;
                    key++;
                }
                else if (gameCount == 1 && IsKeyPressed(KEY_E))
                {
                    // Get the current directory
                    std::filesystem::path currentDir = std::filesystem::current_path();

                    // Append the path to the executable relative to the current directory
                    std::string pathToExecutable = currentDir.string() + "\\minigames\\flappyman\\easyflappy.exe";

                    // Check if the executable file exists
                    if (!std::filesystem::exists(pathToExecutable)) {
                        std::cerr << "Executable file not found: " << pathToExecutable << std::endl;
                        
                    }

                    // Append the "graphics" folder to the current directory
                    std::string graphicsDir = currentDir.string() + "\\minigames\\flappyman";

                    // Set the working directory to the location of the images
                    int result = _chdir(graphicsDir.c_str());
                    if (result != 0) {
                        std::cerr << "Failed to set the working directory. Error code: " << result << std::endl;
                        
                    } else {
                        std::cout << "Working directory successfully set to: " << graphicsDir << std::endl;
                    }

                    // Execute the program
                    result = system(pathToExecutable.c_str());
                    if (result == -1) {
                        std::cerr << "Failed to execute the program. Error code: " << result << std::endl;
                        
                    }
                    key++;

                }

            }
        }

        // Door Checks
        if (playerPos.x <= -30)
        {
            x = 450;
            y = 210;

            currRoomY--;
        }
        else if (playerPos.x >= 475)
        {
            x = -11;
            y = 210;

            currRoomY++;
        }
        else if (playerPos.y >= 415)
        {
            x = 230;
            y = -5;

            currRoomX++;
        }
        else if (playerPos.y <= -40)
        {
            x = 230;
            y = 395;

            currRoomX--;
        }

        if (tileMap[(int)((playerPos.x + 10) / playerSize)][(int)((playerPos.y + 55) / playerSize)] == 3)
        {
            if (key < 1)
            {
                DrawText(TextFormat("Door is locked"), (screenWidth - 150) / 2, screenHeight - 100, 20, WHITE);
            }
            else
            {
                DrawText(TextFormat("Press E to Enter"), (screenWidth - 150) / 2, screenHeight - 100, 20, WHITE);
                if (IsKeyPressed(KEY_E))
                {   
                    x = 450;
                    y = 210;
                    currRoomY--;
                }
            }
        }
        else if (tileMap[(int)((playerPos.x + 5) / playerSize) + 1][(int)((playerPos.y + 55) / playerSize)] == 3)
        {
            if (key < 1)
            {
                DrawText(TextFormat("Door is locked"), (screenWidth - 150) / 2, screenHeight - 100, 20, WHITE);
            }
            else
            {
                DrawText(TextFormat("Press E to Enter"), (screenWidth - 150) / 2, screenHeight - 100, 20, WHITE);
                if (IsKeyPressed(KEY_E))
                {
                    x = -11;
                    y = 210;
                    currRoomY++;
                }
            }
        }
        else if (tileMap[(int)((playerPos.x + 30) / playerSize)][(int)((playerPos.y + 80) / playerSize) - 1] == 3)
        {
            if (key < 1)
            {
                DrawText(TextFormat("Door is locked"), (screenWidth - 150) / 2, screenHeight - 100, 20, WHITE);
            }
            else
            {
                DrawText(TextFormat("Press E to Enter"), (screenWidth - 150) / 2, screenHeight - 100, 20, WHITE);
                if (IsKeyPressed(KEY_E))
                {
                    x = 230;
                    y = 395;
                    currRoomX--;
                }
            }
        }
        else if (tileMap[(int)((playerPos.x + 30) / playerSize)][(int)((playerPos.y + 25) / playerSize) + 1] == 3)
        {
            if (key < 1)
            {
                DrawText(TextFormat("Door is locked"), (screenWidth - 150) / 2, screenHeight - 100, 20, WHITE);
            }
            else
            {
                DrawText(TextFormat("Press E to Enter"), (screenWidth - 150) / 2, screenHeight - 100, 20, WHITE);
                if (IsKeyPressed(KEY_E))
                {
                    x = 230;
                    y = -5;
                    currRoomX++;
                }
            }      
        }

        if (tileMap[(int)((playerPos.x + 10) / playerSize)][(int)((playerPos.y + 55) / playerSize)] == 4)
        {
            if (key < 2)
            {
                DrawText(TextFormat("Final door is locked"), (screenWidth - 150) / 2, screenHeight - 100, 20, WHITE);
            }
            else
            {
                DrawText(TextFormat("Press E to Unlock"), (screenWidth - 150) / 2, screenHeight - 100, 20, WHITE);
                if (IsKeyPressed(KEY_E))
                {
                    finalDoor = true;
                }
            }
        }
        else if (tileMap[(int)((playerPos.x + 5) / playerSize) + 1][(int)((playerPos.y + 55) / playerSize)] == 4)
        {
            if (key < 2)
            {
                DrawText(TextFormat("Final door is locked"), (screenWidth - 150) / 2, screenHeight - 100, 20, WHITE);
            }
            else
            {
                DrawText(TextFormat("Press E to Unlock"), (screenWidth - 150) / 2, screenHeight - 100, 20, WHITE);
                if (IsKeyPressed(KEY_E))
                {
                    finalDoor = true;
                }
            }
        }
        else if (tileMap[(int)((playerPos.x + 30) / playerSize)][(int)((playerPos.y + 80) / playerSize) - 1] == 4)
        {
            if (key < 2)
            {
                DrawText(TextFormat("Final door is locked"), (screenWidth - 150) / 2, screenHeight - 100, 20, WHITE);
            }
            else
            {
                DrawText(TextFormat("Press E to Unlock"), (screenWidth - 150) / 2, screenHeight - 100, 20, WHITE);
                if (IsKeyPressed(KEY_E))
                {
                    finalDoor = true;
                }
            }
        }
        else if (tileMap[(int)((playerPos.x + 30) / playerSize)][(int)((playerPos.y + 25) / playerSize) + 1] == 4)
        {
            if (key < 2)
            {
                DrawText(TextFormat("Final door is locked"), (screenWidth - 150) / 2, screenHeight - 100, 20, WHITE);
            }
            else
            {
                DrawText(TextFormat("Press E to Unlock"), (screenWidth - 150) / 2, screenHeight - 100, 20, WHITE);
                if (IsKeyPressed(KEY_E))
                {
                    finalDoor = true;
                }
            }
        }

        // Update Player Position
        playerPos.x = x;
        playerPos.y = y;

        // Reset Locked doors
        currRoom.resetGhostLocations();

        // For testing and knowing current room index
        // cout << "Room[" << currRoomX << "][" << currRoomY << "]" << endl;

        // Draw the player model at location
        DrawTextureEx(playerModel, playerPos, 0, 2, WHITE);

        // Will show end screen when user exits the final door
        if (playerPos.x >= 475 && roomMap[currRoomX][currRoomY] == "botRight")
        {
            loadEndScreen("Congratulations you won!", playerScore);
        }

        EndDrawing();
    }

    CloseWindow();
}
