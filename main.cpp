#include "raylib.h"
#include "player.cpp"
#include "level_loader.cpp"
#include "button.cpp"
#include<vector>
#include<string>

void DrawControlsInfo()
{
    Texture2D arrows_img = LoadTexture("resources/arrows.png");
    DrawText("Controls", 50, 480, 30, BLACK);
    DrawText("WSAD or", 50, 550, 25, BLACK);
    DrawTexture(arrows_img, 170, 525, WHITE);
}

void DrawWalls(const std::vector<Rectangle> rects)
{
    for(auto rect : rects)
    {
        DrawRectangleRec(rect, BLACK);
    }
}

int main()
{
    const int screen_width = 1000;
    const int screen_height = 700;

    bool has_transition_ended = false;

    bool level_completed = true;
    bool have_levels_ended = false;

    InitWindow(screen_width, screen_height, "squarescape");
    InitAudioDevice();

    //level Loader
    levelLoader loader = levelLoader();

    //audios
    Sound lvl_complete_Sfx = LoadSound("resources/level_complete.mp3");


    //split screen 1
    Player player1 = Player(225, 225);

    //top-left = {25, 25}
    //size = 400x400
    std::vector<Rectangle> screen1_borders;
    screen1_borders.push_back(Rectangle(25, 25, 410,10));
    screen1_borders.push_back(Rectangle(25, 25, 10, 410));
    screen1_borders.push_back(Rectangle(425, 25, 10, 410));
    screen1_borders.push_back(Rectangle(25, 425, 410, 10));
    std::vector<Rectangle> screen1_obstacles;
    levelFinisher screen1_finisher;


    //split screen 2
    Player player2 = Player(775, 225);
    
    //top-left = {565, 25}
    //size = 400x400
    std::vector<Rectangle> screen2_borders;
    screen2_borders.push_back(Rectangle(565, 25, 410,10));
    screen2_borders.push_back(Rectangle(565, 25, 10, 410));
    screen2_borders.push_back(Rectangle(965, 25, 10, 410));
    screen2_borders.push_back(Rectangle(565, 425, 410, 10));
    std::vector<Rectangle> screen2_obstacles;
    levelFinisher screen2_finisher;


    //starting page
    while(!WindowShouldClose())
    {
        Texture2D game_logo = LoadTexture("resources/logo.png");
        BeginDrawing();
            ClearBackground(WHITE);
            DrawTexture(game_logo, 0, 0, WHITE);
        EndDrawing();
        if(IsKeyPressed(257)) // 257 : code for enter
        {
            break;
        }
    }

   //game loop 
   game_loop:
        has_transition_ended = false;
        have_levels_ended = false;
        loader.reset();
        screen1_borders.at(2) = Rectangle(425, 25, 10, 410);
        screen2_borders.at(1) = Rectangle(565, 25, 10, 410);
        while(!WindowShouldClose() && !have_levels_ended)
        {
            if(level_completed)
            {
                WaitTime(0.1); // compensation for audio delay
                Level cur_level = loader.loadNextLevel();

                if(!cur_level.levelExists())
                {
                    have_levels_ended = true;
                    break;
                }

                //reinitialise player pos
                player1.setPos(cur_level.playerPos.first);
                player2.setPos(cur_level.playerPos.second);

                //reinitialise endpoints pos
                screen1_finisher.setPos(cur_level.levelEndpoints.first);
                screen2_finisher.setPos(cur_level.levelEndpoints.second);

                screen1_obstacles = cur_level.levelDesgin.first;
                screen2_obstacles = cur_level.levelDesgin.second;

                level_completed = false;
            }

            if(player1.hasLevelFinished(screen1_finisher) && player2.hasLevelFinished(screen2_finisher))
            {
                PlaySound(lvl_complete_Sfx);
                level_completed = true;
            }

            player1.getMovement();
            player1.ResolveCollisions(screen1_borders);
            player1.ResolveCollisions(screen1_obstacles);
            player2.getMovement();
            player2.ResolveCollisions(screen2_borders);
            player2.ResolveCollisions(screen2_obstacles);
            
            
            BeginDrawing();
                DrawControlsInfo();
                DrawText(("Level: " + std::to_string(loader.getCurLevel())).c_str(), 750, 500, 50, BLACK);

                DrawWalls(screen1_borders);
                DrawWalls(screen2_borders);
                DrawWalls(screen1_obstacles);
                DrawWalls(screen2_obstacles);

                screen1_finisher.Draw(); screen2_finisher.Draw();
                
                DrawRectangleV(player1.getPos(), {player1.getWidth(), player1.getHeight()}, player1.color);
                DrawRectangleV(player2.getPos(), {player2.getWidth(), player2.getHeight()}, player2.color);

                ClearBackground(WHITE);
            EndDrawing();
        }
    

    //transition animation
    //shorten borders
    int transition_speed = 150;

    screen1_borders.at(2) = Rectangle(425, 25, 10, 325);
    screen2_borders.at(1) = Rectangle(565, 25, 10, 325);

    player1.setPos(Vector2(50, 50));
    player2.setPos(Vector2(920, 50));

    screen1_finisher.setPos(Vector2(55, 55));
    screen2_finisher.setPos(Vector2(925, 55));

    while(!WindowShouldClose() && !has_transition_ended)
    {
        float deltaTime = 1.0/GetFPS();

        //player 1 anims
        if(player1.getPosX() == 50 && player1.getPosY() <= 380)
        {
            player1.setPos(Vector2(player1.getPosX(), player1.getPosY() + transition_speed*deltaTime));
        }
        else if(player1.getPosY() >= 380 && player1.getPosX() <= 460)
        {
            player1.setPos(Vector2(player1.getPosX() + transition_speed*deltaTime, player1.getPosY()));
        }
        else if(player1.getPosX() >= 460)
        {
            player1.setPos(Vector2(player1.getPosX(), player1.getPosY() - transition_speed*deltaTime));
        }

        //player 2 anims
        if(player2.getPosX() == 920 && player2.getPosY() <= 380)
        {
            player2.setPos(Vector2(player2.getPosX(), player2.getPosY() + transition_speed*deltaTime));
        }
        else if(player2.getPosY() >= 380 && player2.getPosX() >= 510)
        {
            player2.setPos(Vector2(player2.getPosX() - transition_speed*deltaTime, player2.getPosY()));
        }
        else if(player2.getPosX() <= 510)
        {
            player2.setPos(Vector2(player2.getPosX(), player2.getPosY() - transition_speed*deltaTime));
        }

        if(player1.getPosY() + player1.getHeight() < 0 && player2.getPosY() + player2.getHeight() < 0)
        {
            has_transition_ended = true;
        }

        BeginDrawing();
            ClearBackground(WHITE);
            DrawWalls(screen1_borders);
            DrawWalls(screen2_borders);

            screen1_finisher.Draw(); screen2_finisher.Draw();
            
            DrawRectangleV(player1.getPos(), {player1.getWidth(), player1.getHeight()}, player1.color);
            DrawRectangleV(player2.getPos(), {player2.getWidth(), player2.getHeight()}, player2.color);
        EndDrawing();
    }

    //end screen
    Button play_again = Button("Play again");
    Button quit = Button ("Quit");
    while(!WindowShouldClose() && has_transition_ended)
    {
        Texture2D ending_screen_bg = LoadTexture("resources/ending_screen.png");
        play_again.onHover();
        quit.onHover();
        BeginDrawing();    
            ClearBackground(WHITE);
            DrawTexture(ending_screen_bg, 0, 0, WHITE);        
            play_again.Draw(Vector2(400, 300), Vector2(440, 320));
            quit.Draw(Vector2(400, 425), Vector2(480, 450));
        EndDrawing();

        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            if(play_again.isClicked())
            {
                goto game_loop;
            }
            else if(quit.isClicked())
            {
                break;
            }
        }
    }
    CloseWindow();

    return 0;
}
