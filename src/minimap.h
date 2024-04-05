#ifndef MINIMAP_H
#define MINIMAP_H

#include "raylib.h"

class Minimap {
    public:
        Minimap(int screenWidth, int screenHeight);
            void miniDraw(Vector2 playerPosition, int currentRoomX, int currentRoomY);

    private:
        int screenWidth;
        int screenHeight;
        Vector2 minimapPosition;
        int minimapWidth;
        int minimapHeight;
        int roomWidth;  // Width of a single room in the minimap
        int roomHeight; // Height of a single room in the minimap
        void DrawMiniRoom(int roomX, int roomY);
};

#endif // MINIMAP_H
