#include "minimap.h"

Minimap::Minimap(int screenWidth, int screenHeight)
    : screenWidth(screenWidth), screenHeight(screenHeight), roomWidth(40), roomHeight(40) {
    minimapWidth = roomWidth * 3; // 3 rooms horizontally
    minimapHeight = roomHeight * 3; // 3 rooms vertically
    minimapPosition = {(float)screenWidth - minimapWidth - 20, 20}; // Positioning the minimap on the top-right
}


// IMPLEMENTED WITH THE ASSUMPTION THAT WE ARE TRACKING THE X AND Y OF THE ROOMS
void Minimap::miniDraw(Vector2 playerPosition, int currentRoomX, int currentRoomY) {
    // Draw minimap background
    DrawRectangle(minimapPosition.x - 1, minimapPosition.y - 1, minimapWidth + 2, minimapHeight + 2, BLACK); // Border
    DrawRectangle(minimapPosition.x, minimapPosition.y, minimapWidth, minimapHeight, LIGHTGRAY); // Background

    for (int y = 0; y < 3; ++y) {
        for (int x = 0; x < 3; ++x) {
            DrawMiniRoom(x, y);
        }
    }

    // Draw the player
    float playerMinimapX = minimapPosition.x + currentRoomX * roomWidth + (playerPosition.x / (screenWidth/3)) * roomWidth;
    float playerMinimapY = minimapPosition.y + currentRoomY * roomHeight + (playerPosition.y / (screenHeight/3)) * roomHeight;
    DrawRectangle(playerMinimapX, playerMinimapY, 5, 5, RED); // Player represented as a red dot
}

void Minimap::DrawMiniRoom(int roomX, int roomY) {
    int startX = minimapPosition.x + roomX * roomWidth;
    int startY = minimapPosition.y + roomY * roomHeight;

    Color color = DARKGRAY;

    // Draw the room
    DrawRectangleLines(startX, startY, roomWidth, roomHeight, color);
}
