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
            screen1_endpoint = {350, 225}; screen2_endpoint = {895, 225};
            screen1_playerpos = {75, 225}; screen2_playerpos = {615, 225};
            addLevel(screen1_design, screen2_design, screen1_endpoint, screen2_endpoint, screen1_playerpos, screen2_playerpos);

            //level 1 design
            screen1_design.clear();
            screen1_design.push_back(Rectangle(150, 200, 20, 100));
            screen2_design.clear();
            screen1_endpoint = {225, 225}; screen2_endpoint = {850, 225};
            screen1_playerpos = {375, 225}; screen2_playerpos = {600, 225};
            addLevel(screen1_design, screen2_design, screen1_endpoint, screen2_endpoint, screen1_playerpos, screen2_playerpos);

            //level 2 design
            screen1_design.clear();
            screen1_design.push_back(Rectangle(240, 320, 20, 110));
            screen2_design.clear();
            screen2_design.push_back(Rectangle(575, 130, 150, 10));
            screen2_design.push_back(Rectangle(715, 100, 10, 40));
            screen1_endpoint = {350, 365}; screen2_endpoint = {635, 75};
            screen1_playerpos = {75, 375}; screen2_playerpos = {615, 375};
            addLevel(screen1_design, screen2_design, screen1_endpoint, screen2_endpoint, screen1_playerpos, screen2_playerpos);

            //level 3 design
            screen1_design.clear();
            screen1_design.push_back(Rectangle(100, 150, 20, 150));
            screen1_design.push_back(Rectangle(165, 180, 175, 20));
            screen1_design.push_back(Rectangle(185, 320, 20, 105));
            screen1_design.push_back(Rectangle(265, 245, 170, 20));
            screen1_design.push_back(Rectangle(100, 300, 105, 20));
            screen2_design.clear();
            screen2_design.push_back(Rectangle(640, 145, 160, 20));
            screen2_design.push_back(Rectangle(800, 100, 20, 120));
            screen2_design.push_back(Rectangle(750, 270, 225, 20));
            screen2_design.push_back(Rectangle(870, 130, 95, 20));
            screen1_endpoint = {130, 220 }; screen2_endpoint = {825, 330};
            screen1_playerpos = {50, 375}; screen2_playerpos = {590, 100};
            addLevel(screen1_design, screen2_design, screen1_endpoint, screen2_endpoint, screen1_playerpos, screen2_playerpos);

            //level 4 design
            screen1_design.clear();
            screen1_design.push_back(Rectangle(125, 75, 20, 150));
            screen1_design.push_back(Rectangle(35, 270, 210, 20));
            screen1_design.push_back(Rectangle(270, 75, 20, 130));
            screen1_design.push_back(Rectangle(270, 205, 155, 20));
            screen2_design.clear();
            screen2_design.push_back(Rectangle(670, 150, 20, 275));
            screen2_design.push_back(Rectangle(740, 25, 20, 125));
            screen2_design.push_back(Rectangle(740, 150, 135, 20));
            screen2_design.push_back(Rectangle(875, 100, 20, 200));
            screen1_endpoint = {360, 170}; screen2_endpoint = {800, 125};
            screen1_playerpos = {75, 150}; screen2_playerpos = {600, 150};
            addLevel(screen1_design, screen2_design, screen1_endpoint, screen2_endpoint, screen1_playerpos, screen2_playerpos);

            //level 5 design
            screen1_design.clear();
            screen1_design.push_back(Rectangle(140, 70, 120, 20));
            screen1_design.push_back(Rectangle(140, 140, 190, 20));
            screen1_design.push_back(Rectangle(140, 290, 285, 20));
            screen2_design.clear();
            screen2_design.push_back(Rectangle(665, 80, 20, 180));
            screen2_design.push_back(Rectangle(765, 150, 200, 20));
            screen1_endpoint = {225, 180}; screen2_endpoint = {900,190};
            screen1_playerpos = {375,250}; screen2_playerpos = {715,110};
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

        int getCurLevel()
        {
            return cur_level;
        }

        void reset()
        {
            cur_level = -1;
        }
};