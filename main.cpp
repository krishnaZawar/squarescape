#include "raylib.h"
#include "player.cpp"
#include<vector>

int main()
{
    const int screenWidth = 800;
    const int screenHeight = 800;

    InitWindow(screenWidth, screenHeight, "my first window");

    SetTargetFPS(60);
    
    Player player = Player();

    //sample rectangles setup
    std::vector<Rectangle> rects;
    rects.push_back(Rectangle(100, 100, 100, 100));
    rects.push_back(Rectangle(300, 500, 100, 50));
    rects.push_back(Rectangle(700, 200, 50, 200));
    
    while(!WindowShouldClose())
    {
        player.getMovement();
        player.checkForCollisions(rects);
        
        BeginDrawing();
            for(auto rect : rects)
            {
                DrawRectangleRec(rect, BLUE);
            }
            
            DrawRectangleV(player.pos, {(float)player.width, (float)player.height}, player.color);
            ClearBackground(WHITE);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}