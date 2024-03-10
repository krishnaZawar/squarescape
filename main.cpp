#include "raylib.h"
#include "player.cpp"
#include<vector>

int main()
{
    const int screenWidth = 1000;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "my first window");

    SetTargetFPS(60);

    //split screen 1
    Player player1 = Player(225, 225);

    std::vector<Rectangle> s1_borders;
    s1_borders.push_back(Rectangle(25, 25, 400,10));
    s1_borders.push_back(Rectangle(25, 25, 10, 400));
    s1_borders.push_back(Rectangle(425, 25, 10, 400));
    s1_borders.push_back(Rectangle(25, 415, 400, 10));

    //split screen 2
    Player player2 = Player(75, 225);

    std::vector<Rectangle> s2_borders;
    s2_borders.push_back(Rectangle(565, 25, 400,10));
    s2_borders.push_back(Rectangle(565, 25, 10, 400));
    s2_borders.push_back(Rectangle(965, 25, 10, 400));
    s2_borders.push_back(Rectangle(565, 415, 400, 10));
    
    while(!WindowShouldClose())
    {
        player1.getMovement();
        player1.checkForCollisions(s1_borders);
        player2.getMovement();
        player2.checkForCollisions(s2_borders);
        
        BeginDrawing();
            for(auto border : s1_borders)
            {
                DrawRectangleRec(border, BLACK);
            }
            for(auto border : s2_borders)
            {
                DrawRectangleRec(border, BLACK);
            }
            
            DrawRectangleV(player1.pos, {(float)player1.width, (float)player1.height}, player1.color);
            DrawRectangleV(player2.pos, {(float)player2.width, (float)player2.height}, player2.color);

            ClearBackground(WHITE);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}