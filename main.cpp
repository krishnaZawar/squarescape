#include "raylib.h"
#include "player.cpp"
#include<vector>

bool hasGameStarted = false;

int main()
{
    const int screenWidth = 1000;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "my first window");

    SetTargetFPS(60);

    //split screen 1
    Player player1 = Player(225, 225);

    std::vector<Rectangle> screen1_borders;
    screen1_borders.push_back(Rectangle(25, 25, 400,10));
    screen1_borders.push_back(Rectangle(25, 25, 10, 400));
    screen1_borders.push_back(Rectangle(425, 25, 10, 400));
    screen1_borders.push_back(Rectangle(25, 415, 400, 10));
    
    levelFinisher screen1_finisher = levelFinisher(350, 225);

    //split screen 2
    Player player2 = Player(775, 225);

    std::vector<Rectangle> screen2_borders;
    screen2_borders.push_back(Rectangle(565, 25, 400,10));
    screen2_borders.push_back(Rectangle(565, 25, 10, 400));
    screen2_borders.push_back(Rectangle(965, 25, 10, 400));
    screen2_borders.push_back(Rectangle(565, 415, 400, 10));

    levelFinisher screen2_finisher = levelFinisher(900, 225);

    while(!WindowShouldClose() && !hasGameStarted)
    {
        BeginDrawing();
            ClearBackground(WHITE);
            DrawText("press enter to start", 300, 300, 30, BLACK);
        EndDrawing();
        if(IsKeyPressed(257)) // 257 : code for enter
        {
            hasGameStarted = true;
        }
    }
    
    while(!WindowShouldClose() && hasGameStarted)
    {
        player1.getMovement();
        player1.ResolveCollisions(screen1_borders);
        player2.getMovement();
        player2.ResolveCollisions(screen2_borders);

        if(player1.hasLevelFinished(screen1_finisher) && player2.hasLevelFinished(screen2_finisher))
        {
            //update level
        }
        
        BeginDrawing();
            for(auto border : screen1_borders)
            {
                DrawRectangleRec(border, BLACK);
            }
            for(auto border : screen2_borders)
            {
                DrawRectangleRec(border, BLACK);
            }

            screen1_finisher.Draw(); screen2_finisher.Draw();
            
            DrawRectangleV(player1.pos, {(float)player1.width, (float)player1.height}, player1.color);
            DrawRectangleV(player2.pos, {(float)player2.width, (float)player2.height}, player2.color);

            ClearBackground(WHITE);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
