#include <raylib.h>
#include <string>
#include <iostream>

#ifndef TITLE_VARS
#define TITLE_LOGO "resources/male1.png"
#define TITLE_FONT "resources/RubikScribble-Regular.ttf"
#define TITLE_AUDIO "resources/music.mp3"
#define MAX_INPUT_CHARS 8

// make sure these are from left to right
#define PLAYER_1 "resources/male1.png"
#define playerXPos1 80
#define playerYPos1 64

#define PLAYER_2 "resources/female1.png"
#define playerXPos2 200
#define playerYPos2 64

#define PLAYER_3 "resources/neutral2.png"
#define playerXPos3 320
#define playerYPos3 64

#endif

using namespace std;

static int logoPositionX = 0;
static int logoPositionY = 0;
static int settingsX = 0;
static int settingsY = 0;

static Font font = {0};
static Music music = {0};

void loadTitle();
int getCharNum();
string loadName();
bool IsAnyKeyPressed();

void loadTitle()
{
    // we assume a window is already there.

    font = LoadFont(TITLE_FONT);
    music = LoadMusicStream(TITLE_AUDIO);
    Image logo = LoadImage(TITLE_LOGO);
    Texture titleLogo = LoadTextureFromImage(logo);

    SetTargetFPS(60);

    while (!WindowShouldClose())
    { // uses same game loop but breaks out if title is clicked
        BeginDrawing();
        ClearBackground(RAYWHITE);
        Vector2 logoPos;
        logoPos.x = GetScreenWidth() / 2 - 75;
        logoPos.y = GetScreenHeight() / 2;
        DrawTextureEx(titleLogo, logoPos, 0, 4, WHITE);
        DrawText("Press Enter to Play", GetScreenWidth() / 2 - 215, GetScreenHeight() / 2 - 40, 40, BLACK);

        if (IsKeyPressed(KEY_ENTER))
        {
            // end of function, add all deinitializing here.
            EndDrawing();

            // unload resources
            UnloadMusicStream(music);
            UnloadFont(font);
            UnloadTexture(titleLogo);
            UnloadImage(logo);

            // on to next screen
            return;
        }
        EndDrawing();
    }

    CloseWindow();
}

int getCharNum()
{
    // we assume a window is already there.
    // TODO change 128 and 128 to half the height and width of the logo
    settingsX = GetScreenWidth() / 2 - 200;
    settingsY = GetScreenHeight() / 2 - 20;

    font = LoadFont(TITLE_FONT);
    music = LoadMusicStream(TITLE_AUDIO);

    Image player1 = LoadImage(PLAYER_1);
    Image player2 = LoadImage(PLAYER_2);
    Image player3 = LoadImage(PLAYER_3);

    Texture player1Texture = LoadTextureFromImage(player1);
    Texture player2Texture = LoadTextureFromImage(player2);
    Texture player3Texture = LoadTextureFromImage(player3);

    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(RAYWHITE);
        DrawText("Please Select Your\n\n     Character!", settingsX, settingsY, 40, BLACK);
        DrawText("  1      2      3", settingsX + 50, settingsY - 200, 40, BLACK);

        Vector2 player1Pos;
        player1Pos.x = playerXPos1;
        player1Pos.y = playerYPos1;
        Vector2 player2Pos;
        player2Pos.x = playerXPos2;
        player2Pos.y = playerYPos2;
        Vector2 player3Pos;
        player3Pos.x = playerXPos3;
        player3Pos.y = playerYPos3;

        DrawTextureEx(player1Texture, player1Pos, 0, 4, WHITE);
        DrawTextureEx(player2Texture, player2Pos, 0, 4, WHITE);
        DrawTextureEx(player3Texture, player3Pos, 0, 4, WHITE);
        // DrawTexture(player1Texture, playerXPos1, playerYPos1, RAYWHITE);
        // DrawTexture(player2Texture, playerXPos2, playerYPos2, RAYWHITE);
        // DrawTexture(player3Texture, playerXPos3, playerYPos3, RAYWHITE);

        if (IsKeyPressed(KEY_ONE))
        {
            return 1;
        }
        else if (IsKeyPressed(KEY_TWO))
        {
            return 2;
        }
        else if (IsKeyPressed(KEY_THREE))
        {
            return 3;
        }

        EndDrawing();
    }
    return 1;
}

string loadName()
{

    const int screenWidth = 800;
    const int screenHeight = 450;

    char name[MAX_INPUT_CHARS + 1] = "\0"; // NOTE: One extra space required for null terminator char '\0'
    int letterCount = 0;

    Rectangle textBox = {screenWidth / 2.0f - 260, 180, 225, 50};
    bool mouseOnText = false;

    int framesCounter = 0;

    SetTargetFPS(30); // Set our game to run at 10 frames-per-second

    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {

        if (CheckCollisionPointRec(GetMousePosition(), textBox))
            mouseOnText = true;
        else
            mouseOnText = false;

        if (mouseOnText)
        {
            // Set the window's cursor to the I-Beam
            SetMouseCursor(MOUSE_CURSOR_IBEAM);

            // Get char pressed (unicode character) on the queue
            int key = GetCharPressed();

            // Check if more characters have been pressed on the same frame
            while (key > 0)
            {
                // NOTE: Only allow keys in range [32..125]
                if ((key >= 32) && (key <= 125) && (letterCount < MAX_INPUT_CHARS))
                {
                    name[letterCount] = (char)key;
                    name[letterCount + 1] = '\0'; // Add null terminator at the end of the string.
                    letterCount++;
                }

                key = GetCharPressed(); // Check next character in the queue
            }

            if (IsKeyPressed(KEY_BACKSPACE))
            {
                letterCount--;
                if (letterCount < 0)
                    letterCount = 0;
                name[letterCount] = '\0';
            }
        }

        else
            SetMouseCursor(MOUSE_CURSOR_DEFAULT);

        if (mouseOnText)
            framesCounter++;
        else
            framesCounter = 0;
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawText("Please Enter A Name, Then Press Enter", 40, 140, 20, GRAY);
        DrawRectangleRec(textBox, LIGHTGRAY);

        if (mouseOnText)
            DrawRectangleLines((int)textBox.x, (int)textBox.y, (int)textBox.width, (int)textBox.height, RED);
        else
            DrawRectangleLines((int)textBox.x, (int)textBox.y, (int)textBox.width, (int)textBox.height, DARKGRAY);

        DrawText(name, (int)textBox.x + 5, (int)textBox.y + 8, 40, MAROON);
        DrawText(TextFormat("Name Length: %i/%i", letterCount, MAX_INPUT_CHARS), 160, 250, 20, DARKGRAY);

        if (mouseOnText)
        {
            if (letterCount < MAX_INPUT_CHARS)
            {
                // Draw blinking underscore char
                if (((framesCounter / 20) % 2) == 0)
                    DrawText("_", (int)textBox.x + 8 + MeasureText(name, 40), (int)textBox.y + 12, 40, MAROON);
            }
            else
                DrawText("At Character Limit", 158, 300, 20, GRAY);
        }

        EndDrawing();
        //----------------------------------------------------------------------------------
        if (IsKeyPressed(KEY_ENTER))
        {
            // end of function, add all deinitializing here.
            EndDrawing();

            // on to next screen
            return string(name);
        }
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow(); // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return string(name); // here for completeness
}

void loadEndScreen(const char *endScreenMsg, int playerScore)
{
    // we assume a window is already there.
    font = LoadFont(TITLE_FONT);
    music = LoadMusicStream(TITLE_AUDIO);
    // Image logo = LoadImage(TITLE_LOGO);
    // Texture titleLogo = LoadTextureFromImage(logo);

    SetTargetFPS(60);

    while (!WindowShouldClose())
    { // uses same game loop but breaks out if title is clicked
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // DrawTexture(titleLogo, GetScreenWidth() / 2, GetScreenHeight() / 2, WHITE);
        DrawText(endScreenMsg, GetScreenWidth() / 2 - 145, (GetScreenHeight() / 2) - 80, 24, BLACK);
        DrawText(TextFormat("Score: %d", playerScore), GetScreenWidth() / 2 - 40, GetScreenHeight() / 2, 24, BLACK);

        DrawText(TextFormat("Press ENTER to play again!"), GetScreenWidth() / 2 - 150, GetScreenHeight() / 2 + 60, 24, BLACK);

        if (IsKeyPressed(KEY_ENTER))
        {
            // end of function, add all deinitializing here.
            EndDrawing();

            // unload resources
            UnloadMusicStream(music);
            UnloadFont(font);
            // UnloadTexture(titleLogo);
            // UnloadImage(logo);

            // on to next screen
            return;
        }
        EndDrawing();
    }

    CloseWindow();
}

// Check if any key is pressed
// NOTE: We limit keys check to keys between 32 (KEY_SPACE) and 126
bool IsAnyKeyPressed()
{
    bool keyPressed = false;
    int key = GetKeyPressed();

    if ((key >= 32) && (key <= 126))
        keyPressed = true;

    return keyPressed;
}