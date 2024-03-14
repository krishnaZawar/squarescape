#include "raylib.h"
#include "player.cpp"
#include "level_loader.cpp"
#include<vector>


void DrawControlsInfo()
{
    Texture2D arrows_img = LoadTexture("images/arrows.png");
    DrawText("Controls", 50, 475, 30, BLACK);
    DrawText("WSAD or", 50, 530, 20, BLACK);
    DrawTexture(arrows_img, 140, 510, WHITE);
}

int main()
{
    const int screenWidth = 1000;
    const int screenHeight = 700;

    bool hasGameStarted = false;
    bool hasGameEnded = false;
    bool levelCompleted = true;

    InitWindow(screenWidth, screenHeight, "my first window");

    SetTargetFPS(60);

    //level Loader
    levelLoader loader = levelLoader();



    //split screen 1
    Player player1 = Player(225, 225);

    //top-left = {25, 25}
    //size = 400x400
    std::vector<Rectangle> screen1_borders;
    screen1_borders.push_back(Rectangle(25, 25, 400,10));
    screen1_borders.push_back(Rectangle(25, 25, 10, 400));
    screen1_borders.push_back(Rectangle(425, 25, 10, 400));
    screen1_borders.push_back(Rectangle(25, 415, 400, 10));
    std::vector<Rectangle> screen1_obstacles;
    levelFinisher screen1_finisher;



    //split screen 2
    Player player2 = Player(775, 225);
    
    //top-left = {565, 25}
    //size = 400x400
    std::vector<Rectangle> screen2_borders;
    screen2_borders.push_back(Rectangle(565, 25, 400,10));
    screen2_borders.push_back(Rectangle(565, 25, 10, 400));
    screen2_borders.push_back(Rectangle(965, 25, 10, 400));
    screen2_borders.push_back(Rectangle(565, 415, 400, 10));
    std::vector<Rectangle> screen2_obstacles;
    levelFinisher screen2_finisher;

    while(!WindowShouldClose() && !hasGameStarted)
    {
        Texture2D game_logo = LoadTexture("images/logo.png");
        BeginDrawing();
            ClearBackground(WHITE);
            DrawTexture(game_logo, 37, 50, WHITE);
            DrawText("press enter to start", 350, 500, 30, BLACK);
        EndDrawing();
        if(IsKeyPressed(257)) // 257 : code for enter
        {
            hasGameStarted = true;
        }
    }
    
    while(!WindowShouldClose() && hasGameStarted && !hasGameEnded)
    {
        if(levelCompleted)
        {
            Level cur_level = loader.loadNextLevel();

            if(!cur_level.levelExists())
            {
                hasGameEnded = true;
                break;
            }

            //reinitialise player pos
            player1.pos = cur_level.playerPos.first;
            player2.pos = cur_level.playerPos.second;

            //reinitialise endpoints pos
            screen1_finisher.setPos(cur_level.levelEndpoints.first);
            screen2_finisher.setPos(cur_level.levelEndpoints.second);

            screen1_obstacles = cur_level.levelDesgin.first;
            screen2_obstacles = cur_level.levelDesgin.second;

            levelCompleted = false;
        }

        if(player1.hasLevelFinished(screen1_finisher) && player2.hasLevelFinished(screen2_finisher))
        {
            levelCompleted = true;
        }

        player1.getMovement();
        player1.ResolveCollisions(screen1_borders);
        player1.ResolveCollisions(screen1_obstacles);
        player2.getMovement();
        player2.ResolveCollisions(screen2_borders);
        player2.ResolveCollisions(screen2_obstacles);
        
        
        BeginDrawing();
            DrawControlsInfo();
            for(auto border : screen1_borders)
            {
                DrawRectangleRec(border, BLACK);
            }
            for(auto border : screen2_borders)
            {
                DrawRectangleRec(border, BLACK);
            }
            for(auto obstacle : screen1_obstacles)
            {
                DrawRectangleRec(obstacle, BLACK);
            }
            for(auto obstacle : screen2_obstacles)
            {
                DrawRectangleRec(obstacle, BLACK);
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
