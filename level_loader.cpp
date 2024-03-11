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
        }

        Level loadNextLevel()
        {
            cur_level++;
            if(cur_level >= (int)levelDesgin.size())
            {
                return Level();
            }
            return Level(levelDesgin.at(cur_level), levelEndpoints.at(cur_level), playerPos.at(cur_level), true);
        }
};