#include <raylib.h>
#include<vector>
#include "level_finisher.cpp"

class Player
{
    Vector2 prev_pos;
    Vector2 pos;

    int width;
    int height;

    int speed;

    void defaultSettings()
    {
        color = RED;
        width = height = 30;
        speed = 150; // set in pixels/second
    }
    public:
        Color color;

        Player(){}

        //passing parameters to set players to their respective screens
        Player(int posX, int posY)
        {
            pos.x = posX;
            pos.y = posY;
            prev_pos = pos;
            defaultSettings();
        }

        //player movement is grid based
        //moves on the basis of arrow keys and WSAD
        void getMovement()
        {
            prev_pos = pos;
            float deltaTime = 1.0/GetFPS();
            if(IsKeyDown('W') || IsKeyDown(265))
            {
                pos.y -= speed * deltaTime;
            }
            else if(IsKeyDown('S') || IsKeyDown(264))
            {
                pos.y += speed * deltaTime;
            }
            else if(IsKeyDown('A') || IsKeyDown(263))
            {
                pos.x -= speed * deltaTime;
            }
            else if(IsKeyDown('D') ||IsKeyDown(262))
            {
                pos.x += speed * deltaTime;
            }
        }


        void ResolveCollisions(const std::vector<Rectangle> &rects)
        {
            for(auto rect : rects)
            {
                resolveCollision(rect);
            }
        }

        //check collisions with one rectangle
        int checkCollision(const Rectangle &rect)
        {
            //side = 0 no collision
            //side = 1 top
            //side = 2 right
            //side = 3 bottom
            //side = 4 left
            int side = 0;

            //top check
            if(pos.y + height > rect.y && pos.y < rect.y && prev_pos.x == pos.x)
            {
                if(pos.x + width > rect.x && pos.x < rect.x)
                {
                    side = 1;
                }
                else if(pos.x + width <= rect.x + rect.width && pos.x >= rect.x)
                {
                    side = 1;
                }
                else if(pos.x < rect.x + rect.width  && pos.x + width > rect.x + rect.width)
                {
                    side = 1;
                }
            }

            //bottom check
            if(pos.y + height > rect.y + rect.height && pos.y < rect.y + rect.height && prev_pos.x == pos.x)
            {
                if(pos.x + width > rect.x && pos.x < rect.x)
                {
                    side = 3;
                }
                else if(pos.x + width <= rect.x + rect.width && pos.x >= rect.x)
                {
                    side = 3;
                }
                else if(pos.x < rect.x + rect.width  && pos.x + width > rect.x + rect.width)
                {
                    side = 3;
                }
            }

            //right check
            if(pos.x < rect.x + rect.width && pos.x + width > rect.x + rect.width && prev_pos.y == pos.y)
            {
                if(pos.y + height > rect.y && pos.y < rect.y)
                {
                    side = 2;
                }
                else if(pos.y >= rect.y && pos.y + height <= rect.y + rect.height)
                {
                    side = 2;
                }
                else if(pos.y < rect.y + rect.height && pos.y + height > rect.y + rect.height)
                {
                    side = 2;
                }
            }

            //left check
            if(pos.x + width >  rect.x && pos.x < rect.x && prev_pos.y == pos.y)
            {
                if(pos.y + height > rect.y && pos.y < rect.y)
                {
                    side = 4;
                }
                else if(pos.y >= rect.y && pos.y + height <= rect.y + rect.height)
                {
                    side = 4;
                }
                else if(pos.y < rect.y + rect.height && pos.y + height > rect.y + rect.height)
                {
                    side = 4;
                }
            }

            //no collision
            return side;
        }

        void resolveCollision(const Rectangle &rect)
        {
            int side = checkCollision(rect);
            if(side == 1)
            {
                pos.y = rect.y - height;
            }
            else if(side == 2)
            {
                pos.x = rect.x + rect.width;
            }
            else if(side == 3)
            {
                pos.y = rect.y + rect.height;
            }
            else if(side == 4)
            {
                pos.x = rect.x - width;
            }
        }

        bool hasLevelFinished(levelFinisher &finisher)
        {
            Vector2 pos = finisher.getPos();
            if(checkCollision(Rectangle(pos.x, pos.y, finisher.getWidth(), finisher.getHeight())))
            {
                return true;
            }
            return false;
        }

        void setPos(Vector2 newPos) 
        {
            pos = newPos;
        }

        Vector2 getPos()
        {
            return pos;
        }
        float getPosX()
        {
            return pos.x;
        }
        float getPosY()
        {
            return pos.y;
        }

        float getWidth()
        {
            return width;
        }
        float getHeight()
        {
            return height;
        }
};
