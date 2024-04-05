#include <raylib.h>
#include <iostream>

int player_score = 0;
int cpu_score = 0;
int playerBounces = 1;

class Ball {
public:
    float x, y;
    int speed_x, speed_y;
    int radius;

    void Draw() {
        DrawCircle(x, y, radius, WHITE);
    }

    void Update() {
        x += speed_x;
        y += speed_y;

        if (y + radius >= GetScreenHeight() || y - radius <= 0) {
            speed_y *= -1;
        }

        // Cpu wins
        if (x + radius >= GetScreenWidth()) {
            cpu_score++;
            ResetBall();
        }

        if (x - radius <= 0) {
            player_score++;
            ResetBall();
            playerBounces = 1; // Reset the player's bounce count when they score
        }
    }

    void ResetBall() {
        x = GetScreenWidth() / 2;
        y = GetScreenHeight() / 2;

        int speed_choices[2] = {-1, 1};
        speed_x *= speed_choices[GetRandomValue(0, 1)];
        speed_y *= speed_choices[GetRandomValue(0, 1)];
    }
};

class Paddle {
protected:
    void LimitMovement() {
        if (y <= 0) {
            y = 0;
        }
        if (y + height >= GetScreenHeight()) {
            y = GetScreenHeight() - height;
        }
    }

public:
    float x, y;
    float width, height;
    int speed;

    void Draw() {
        DrawRectangleRounded(Rectangle{x, y, width, height}, 0.8, 0, WHITE);
    }

    void Update() {
        if (IsKeyDown(KEY_UP)) {
            y -= speed;
        }
        if (IsKeyDown(KEY_DOWN)) {
            y += speed;
        }
        LimitMovement();
    }
};

class CpuPaddle : public Paddle {
public:
    void Update(int ball_y) {
        // Intentionally miss every third time the player bounces the ball - you can adjust based on difficulty levl. 
        if (playerBounces % 4 != 0) {
            if (y + height / 2 > ball_y) {
                y -= speed;
            }
            if (y + height / 2 <= ball_y) {
                y += speed;
            }
            LimitMovement();
        } else {
            
            // Opposite movement
            if (y + height / 2 > ball_y) {
                y += speed;
            }
            if (y + height / 2 <= ball_y) {
                y -= speed;
            }
            LimitMovement();
        }
    }
};


Ball ball;
Paddle player;
CpuPaddle cpu;

void DisplayMessage(const char* message, int fontSize, Color color) {
    DrawText(message, GetScreenWidth() / 2 - MeasureText(message, fontSize) / 2, GetScreenHeight() / 2 - fontSize / 2, fontSize, color);
}

int main() {
    std::cout << "Commencing the game" << std::endl;
    const int screen_width = 1280;
    const int screen_height = 800;
    InitWindow(screen_width, screen_height, "My Pong Game!");
    SetTargetFPS(40);
    ball.radius = 20;
    ball.x = screen_width / 2;
    ball.y = screen_height / 2;
    ball.speed_x = 7;
    ball.speed_y = 7;

    player.width = 25;
    player.height = 170;
    player.x = screen_width - player.width - 60;
    player.y = screen_height / 2 - player.height / 2;
    player.speed = 11;

    cpu.height = 170;
    cpu.width = 25;
    cpu.x = 60;
    cpu.y = screen_height / 2 - cpu.height / 2;
    cpu.speed = 8;

    bool game_over = false;


    while (WindowShouldClose() == false && game_over == false) {
        BeginDrawing();

        // Updating

        ball.Update();
        player.Update();
        cpu.Update(ball.y);

        // Checking for collisions
        if (CheckCollisionCircleRec({ball.x, ball.y}, ball.radius, {player.x, player.y, player.width, player.height})) {
            ball.speed_x *= -1;
            playerBounces++;
        }

        if (CheckCollisionCircleRec({ball.x, ball.y}, ball.radius, {cpu.x, cpu.y, cpu.width, cpu.height})) {
            ball.speed_x *= -1;
        }

        // Drawing
        ClearBackground(BLACK);

        ball.Draw();
        cpu.Draw();
        player.Draw();
        DrawText(TextFormat("%i", cpu_score), screen_width / 4 - 20, 20, 80, WHITE);
        DrawText(TextFormat("%i", player_score), 3 * screen_width / 4 - 20, 20, 80, WHITE);

        // Check win/lose condition
        if (player_score >= 3) {
            game_over = true;
        } else if (cpu_score >= 3) {
            game_over = true;
        }


        EndDrawing();

    }
     // Delay before closing the window
    int delayCounter = 0;
    while (!WindowShouldClose() && delayCounter < 120) { // 240 frames at 40 FPS is roughly 6 seconds
        delayCounter++;
        BeginDrawing();
        ClearBackground(BLACK);

        if (player_score >= 3) {
        DisplayMessage("You won!", 40, GREEN);
        game_over = true;
        } else if (cpu_score >= 3) {
        DisplayMessage("You lose!", 40, RED);
        game_over = true;
        }


        EndDrawing();
    }


    CloseWindow();
    return 0;
}