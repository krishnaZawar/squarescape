#include<raylib.h>
#include<vector>

#include "level.cpp"

class levelLoader
{
    int cur_level;
    
    std::vector<std::pair<std::vector<Rectangle>, std::vector<Rectangle>>> levelDesgin;
    std::vector<std::pair<Vector2, Vector2>> levelEndpoints;
    std::vector<std::pair<Vector2, Vector2>> playerPos;

    void addLevel(std::vector<Rectangle> screen1_design, std::vector<Rectangle> screen2_design, Vector2 screen1_endpoint, Vector2 screen2_endpoint, Vector2 screen1_playerpos, Vector2 screen2_playerpos)
    {
        levelDesgin.push_back(std::make_pair(screen1_design, screen2_design));
        levelEndpoints.push_back(std::make_pair(screen1_endpoint, screen2_endpoint));
        playerPos.push_back(std::make_pair(screen1_playerpos, screen2_playerpos));
    }
    
    public:
        levelLoader()
        {
            //game not started
            cur_level = -1;

            std::vector<Rectangle> screen1_design;
            std::vector<Rectangle> screen2_design;

            Vector2 screen1_endpoint;
            Vector2 screen2_endpoint;

            Vector2 screen1_playerpos;
            Vector2 screen2_playerpos;

            //level 0 design
            screen1_design.clear(); screen2_design.clear();
            screen1_endpoint = {375, 225}; screen2_endpoint = {915, 225};
            screen1_playerpos = {75, 225}; screen2_playerpos = {615, 225};
            addLevel(screen1_design, screen2_design, screen1_endpoint, screen2_endpoint, screen1_playerpos, screen2_playerpos);

            //level 1 design
            screen1_design.clear();
            screen1_design.push_back(Rectangle(150, 200, 30, 100));
            screen2_design.clear();
            screen1_endpoint = {225, 225}; screen2_endpoint = {850, 225};
            screen1_playerpos = {375, 225}; screen2_playerpos = {600, 225};
            addLevel(screen1_design, screen2_design, screen1_endpoint, screen2_endpoint, screen1_playerpos, screen2_playerpos);

            //level 2 design
            screen1_design.clear();
            screen1_design.push_back(Rectangle(240, 320, 20, 100));
            screen2_design.clear();
            screen2_design.push_back(Rectangle(575, 130, 150, 10));
            screen2_design.push_back(Rectangle(715, 100, 10, 40));
            screen1_endpoint = {350, 365}; screen2_endpoint = {635, 75};
            screen1_playerpos = {75, 375}; screen2_playerpos = {615, 375};
            addLevel(screen1_design, screen2_design, screen1_endpoint, screen2_endpoint, screen1_playerpos, screen2_playerpos);

            //level 3 design
            screen1_design.clear();
            screen1_design.push_back(Rectangle(125, 75, 30, 150));
            screen1_design.push_back(Rectangle(35, 270, 200, 30));
            screen1_design.push_back(Rectangle(270, 75, 30, 130));
            screen1_design.push_back(Rectangle(270, 205, 155, 30));
            screen1_design.push_back(Rectangle(350, 25, 10, 50));
            screen2_design.clear();
            screen2_design.push_back(Rectangle(670, 150, 30, 275));
            screen2_design.push_back(Rectangle(740, 25, 30, 125));
            screen2_design.push_back(Rectangle(740, 150, 135, 30));
            screen2_design.push_back(Rectangle(875, 150, 30, 150));
            screen1_endpoint = {375, 150}; screen2_endpoint = {915, 200};
            screen1_playerpos = {75, 150}; screen2_playerpos = {600, 150};
            addLevel(screen1_design, screen2_design, screen1_endpoint, screen2_endpoint, screen1_playerpos, screen2_playerpos);

            //level 4 design
            screen1_design.clear();
            screen2_design.clear();
            screen1_endpoint = {300, 275}; screen2_endpoint = {900, 150};
            screen1_playerpos = {50, 375}; screen2_playerpos = {650, 150};
            addLevel(screen1_design, screen2_design, screen1_endpoint, screen2_endpoint, screen1_playerpos, screen2_playerpos);
        }

        Level loadNextLevel()
        {
            cur_level++;
            if(cur_level >= (int)levelDesgin.size())
            {
                return Level();
            }
            return Level(levelDesgin.at(cur_level), levelEndpoints.at(cur_level), playerPos.at(cur_level));
        }
};