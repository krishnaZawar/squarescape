#include<vector>
#include<raylib.h>

class Level
{
    bool exists;
    public:
        std::pair<std::vector<Rectangle>, std::vector<Rectangle>> levelDesgin;
        std::pair<Vector2, Vector2> levelEndpoints;
        std::pair<Vector2, Vector2> playerPos;

        Level() 
        {
            exists = false;
        }

        Level(std::pair<std::vector<Rectangle>, std::vector<Rectangle>> levelDesgin, std::pair<Vector2, Vector2> levelEndpoints,   std::pair<Vector2, Vector2> playerPos)
        {
            this->levelDesgin = levelDesgin;
            this->levelEndpoints = levelEndpoints;
            this->playerPos = playerPos;
            exists = true;
        }

        bool levelExists()
        {
            return exists;
        }
};