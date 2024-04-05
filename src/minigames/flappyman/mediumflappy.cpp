#include "raylib.h"


void DisplayMessage(const char* message, int fontSize, Color color) {
        DrawText(message, GetScreenWidth() / 2 - MeasureText(message, fontSize) / 2, GetScreenHeight() / 2 - fontSize / 2, fontSize, color);
        }

int main(void){
    float scaleFactor = 1.0f; // Initial scale factor
    float scaleFactorPipeX=1.5f;
    float scaleFactorPipeY= 5.0f;
    float playerGraphicScale = 2.0f;
    float scaleIncrement = 0.01f; 


    const int screenWidth = 1280;
    const int screenHeight = 800;

    // screen size
    const int originalScreenWidth = 288;
    const int originalScreenHeight = 512;

    // Scale factors for adjusting pipe positions
    float scaleX = (float)screenWidth / originalScreenWidth;
    float scaleY = (float)screenHeight / originalScreenHeight;

    
    int pipeWidth = 50; 
    int pipeHeight = 200; 
    // int gap = 200;      
    // int pipeSpeed = 1; 
    
    int Pipe1X = 300 * scaleX;
    int Pipe1Y = 330 * scaleY ;
    int Pipe2X = 500 * scaleX;
    int Pipe2Y = 330 * scaleY;
    int Pipe3X = 700 * scaleX;
    int Pipe3Y = 330 * scaleY;

    int adjustedGapForPipeDown = (int)(320 * scaleY);
    int gap = 250;


    int Scene = 0;
    
    float PlayerY = screenHeight/2;

    InitWindow(screenWidth, screenHeight, "Flappy Bird - Raylib");


    Image backgroundI = LoadImage("graphics/background.png");
    Texture2D background = LoadTextureFromImage(backgroundI);
    

    Image pipedownI = LoadImage("graphics/pipedown.png");
    Texture2D pipeDown = LoadTextureFromImage(pipedownI);
    Image pipeupI = LoadImage("graphics/pipeup.png");
    Texture2D pipeUp = LoadTextureFromImage(pipeupI);

    Image male1I = LoadImage("graphics/male1.png");
    Texture2D male1 = LoadTextureFromImage(male1I);
    Image male2I = LoadImage("graphics/male2.png");
    Texture2D male2 = LoadTextureFromImage(male2I);
    Image male3I = LoadImage("graphics/male3.png");
    Texture2D male3 = LoadTextureFromImage(male3I);
    Texture2D CurText;

    Image messageI = LoadImage("graphics/message.png");
    Texture2D message = LoadTextureFromImage(messageI);

    // //message
    // int messageWidth = message.width ; 
    // int messageHeight = message.height; 
    // int messageX = (screenWidth - messageWidth) / 2; 
    // int messageY = (screenHeight - messageHeight) / 2; 

    UnloadImage(backgroundI);
    UnloadImage(pipedownI);
    UnloadImage(pipeupI);
    UnloadImage(male1I);
    UnloadImage(male2I);
    UnloadImage(male3I);
    UnloadImage(messageI);
    SetTargetFPS(70);

    Rectangle destRect = { 0, 0, screenWidth, screenHeight };
    Rectangle pipeDownRect = {0, 0, pipeWidth, pipeHeight}; 
    //    DrawTexturePro(pipeDown, pipeDownRect, (Rectangle){Pipe1X, bottomPipeYPosition, pipeWidth, pipeHeight}, (Vector2){0, 0}, 0.0f, WHITE);


    
    bool Dead = false;
    bool Enviro = false;
    bool Pressed = true;
    bool DidHit = false;
    
    int framesCounter;
    
    bool wait = false;

    int score = 0;
    while (!WindowShouldClose())
    {
        BeginDrawing();

            if(Scene == 0)
            {
                CurText = male1;
                ClearBackground(RAYWHITE);
                
                Pipe1X = 300;
                Pipe2X = 700;
                Pipe3X = 1100;
                
                DrawTexturePro(background, (Rectangle){ 0.0f, 0.0f, (float)background.width, (float)-background.height }, destRect, (Vector2){ 0, 0 }, 0.0f, WHITE);
                
                PlayerY = screenHeight/2;
                DrawTextureEx(CurText, (Vector2){ screenWidth / 2 - 30, PlayerY }, 0.0f, playerGraphicScale, WHITE);
                //scaleFactorPipeX

                Pipe1Y = GetRandomValue(350, 570) + GetRandomValue(10, 20);
                Pipe2Y = GetRandomValue(350, 570) + GetRandomValue(10, 20);
                Pipe3Y = GetRandomValue(350, 570) + GetRandomValue(10, 20);



             
                
                // Pipe1Y = GetRandomValue(800, 801) + GetRandomValue(400, 401);
                // Pipe2Y = GetRandomValue(800, 801) + GetRandomValue(400, 401);
                // Pipe3Y = GetRandomValue(800, 801) + GetRandomValue(400, 401);
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) Scene = 1;
                Dead = false;
                Enviro = true;
                wait = false;

                int messageWidth = message.width * scaleFactor; // Scale the message width
                int messageHeight = message.height * scaleFactor; // Scale the message height
                int messageX = (screenWidth - messageWidth) / 2; 
                int messageY = (screenHeight - messageHeight) / 2 +150; 

                DrawTextureEx(message, (Vector2){messageX, messageY}, 0.0f, scaleFactor, WHITE);

                scaleFactor += scaleIncrement;
                
                scaleFactor = (scaleFactor > 2.0f) ? 2.0f : scaleFactor;
            }
            if(Scene == 1)
            {
                if(Pipe1X < 127 && Pipe1X >= 126)
                {
                    score++;                    
                }
                if(Pipe2X < 127 && Pipe2X >= 126)
                {
                    score++;
                }
                if(Pipe3X < 127 && Pipe3X >= 126)
                {
                    score++;
                }
                if(Pipe1X <= 158 && Pipe1X >= 127-34)
                {
                    if(PlayerY >= Pipe1Y-24)
                    {
                        Enviro = false;
                        if(DidHit == false)
                        {
                            DidHit = true;
                        }
                    }
                    if(PlayerY <= Pipe1Y-gap)
                    {
                        Enviro = false;
                        if(DidHit == false)
                        {
                            DidHit = true;
                        }                       
                    }DrawTexturePro(background, (Rectangle){ 0.0f, 0.0f, (float)background.width, (float)-background.height }, destRect, (Vector2){ 0, 0 }, 0.0f, WHITE);
                    
                    //
                }
                
                if(Pipe2X <= 158 && Pipe2X >= 127-34)
                {
                    if(PlayerY >= Pipe2Y-24)
                    {
                        Enviro = false;
                        if(DidHit == false)
                        {
                            DidHit = true;
                        }
                    }
                    if(PlayerY <= Pipe2Y-gap)
                    {
                        Enviro = false;
                        if(DidHit == false)
                        {
                            DidHit = true;
                        }
                    }
                    
                    //
                }
                
                if(Pipe3X <= 158 && Pipe3X >= 127-34)
                {
                    if(PlayerY >= Pipe3Y-24)
                    {
                        Enviro = false;
                        if(DidHit == false)
                        {
                            DidHit = true;
                        }
                    }
                    if(PlayerY <= Pipe3Y-gap)
                    {
                        Enviro = false;   
                        if(DidHit == false)
                        {
                            DidHit = true;
                        }                       
                    }
                    
                    //
                }
                
                if(PlayerY >= 800)
                {
                    Dead = true;

                    int delayCounter = 0;

                    while (!WindowShouldClose() && delayCounter < 280) { // 240 frames at 40 FPS is roughly 6 seconds

                        BeginDrawing();
                        ClearBackground(BLACK);
        
                        DisplayMessage ("You Lose!", 40, RED);
                        
                        delayCounter++;


                        EndDrawing();
                    }

                    
                    break;
                    Enviro = false;
                    if(DidHit == false)
                    {
                        DidHit = true;
                    }
                }
                
                if(Dead == false)
                {
                    if(wait == false)
                    {
                        PlayerY+=2; 
                    }
                    else
                    {
                        framesCounter++;

                        if (((framesCounter/2)%2) == 1)
                        {
                            CurText = male1;
                           
                        }
                        if (((framesCounter/4)%2) == 1)
                        {
                            CurText = male2;
                            
                        }
                        if (((framesCounter/6)%2) == 1)
                        {
                            CurText = male3;
                            
                        }
                        if (((framesCounter/8)%2) == 1)
                        {
                            CurText = male2;
                            
                        }
                        if (((framesCounter/10)%2) == 1)
                        {
                            CurText = male1;
                            wait = false;
                            framesCounter = 0;
                        }
                    }
                       
                }
                if(Enviro == true)
                {
                    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && Pressed == false) 
                    {
                        PlayerY -= 40;
                        wait = true;
                        Pressed = true;
                    }
                    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) 
                    {
                        //PlayerY -= 20;
                        Pressed = false;
                    }
                                    
                    Pipe1X -= 1;
                    Pipe2X -= 1;
                    Pipe3X -= 1;
                }
                
                ClearBackground(RAYWHITE);
                DrawTexturePro(background, (Rectangle){ 0.0f, 0.0f, (float)background.width, (float)-background.height }, destRect, (Vector2){ 0, 0 }, 0.0f, WHITE);

                //
                if (Pipe1X <= -52)
                {
                    Pipe1X = Pipe3X + (int)(400);
                    Pipe1Y = (int)((GetRandomValue(350, 570) + GetRandomValue(10, 20)));
                }
                if (Pipe2X <= -52)
                {
                    Pipe2X = Pipe1X + (int)(400);
                    Pipe2Y = (int)((GetRandomValue(350, 570) + GetRandomValue(10, 20)));
                }
                if (Pipe3X <= -52)
                {
                    Pipe3X = Pipe2X + (int)(400);
                    Pipe3Y = (int)((GetRandomValue(350, 570) + GetRandomValue(10, 20)));
                }

                // Render the pipes

                DrawTexturePro(pipeUp, (Rectangle){0, 0, pipeUp.width, pipeUp.height}, (Rectangle){Pipe1X, Pipe1Y, pipeUp.width * scaleFactorPipeX, pipeUp.height * scaleFactorPipeY}, (Vector2){0, 0}, 0.0f, WHITE);
                DrawTexturePro(pipeDown, (Rectangle){0, 0, pipeDown.width, pipeDown.height}, (Rectangle){Pipe1X, Pipe1Y - gap - adjustedGapForPipeDown, pipeDown.width * scaleFactorPipeX, pipeDown.height * scaleFactorPipeY}, (Vector2){0, 0}, 0.0f, WHITE);

                DrawTexturePro(pipeUp, (Rectangle){0, 0, pipeUp.width, pipeUp.height}, (Rectangle){Pipe2X, Pipe2Y, pipeUp.width * scaleFactorPipeX, pipeUp.height * scaleFactorPipeY}, (Vector2){0, 0}, 0.0f, WHITE);
                DrawTexturePro(pipeDown, (Rectangle){0, 0, pipeDown.width, pipeDown.height}, (Rectangle){Pipe2X, Pipe2Y - gap - adjustedGapForPipeDown, pipeDown.width * scaleFactorPipeX, pipeDown.height * scaleFactorPipeY}, (Vector2){0, 0}, 0.0f, WHITE);

                DrawTexturePro(pipeUp, (Rectangle){0, 0, pipeUp.width, pipeUp.height}, (Rectangle){Pipe3X, Pipe3Y, pipeUp.width * scaleFactorPipeX, pipeUp.height * scaleFactorPipeY}, (Vector2){0, 0}, 0.0f, WHITE);
                DrawTexturePro(pipeDown, (Rectangle){0, 0, pipeDown.width, pipeDown.height}, (Rectangle){Pipe3X, Pipe3Y - gap - adjustedGapForPipeDown, pipeDown.width * scaleFactorPipeX, pipeDown.height * scaleFactorPipeY}, (Vector2){0, 0}, 0.0f, WHITE);
                                
                
                                
                DrawText(TextFormat("SCORE: %i", score), 1, 1, 20, BLACK);
                DrawText(TextFormat("SCORE: %i", score), 0, 0, 20, WHITE);
                DrawTextureEx(CurText, (Vector2){ 127, PlayerY }, 0.0f, playerGraphicScale, WHITE);
                
                if (score >= 6){
                    int delayCounter =0; 

                    while (!WindowShouldClose() && delayCounter < 280) { // 240 frames at 40 FPS is roughly 6 seconds

                        BeginDrawing();
                        ClearBackground(BLACK);

                        DisplayMessage("You won!", 40, GREEN);
                        delayCounter++;


                        EndDrawing();
                    } 
                    break;

                }
                    
                
            }
            

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
    




    