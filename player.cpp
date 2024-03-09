#include <raylib.h>
#include<vector>

class Player
{
    public:
        Vector2 pos;

        int width;
        int height;

        int speed;

        Color color;

        Player()
        {
            pos.x = GetScreenWidth()/2;
            pos.y= GetScreenHeight()/2;

            color = RED;

            width = height = 50;

            speed = 5;
        }

        //player movement is grid based
        //moves on the basis of arrow keys and WSAD
        void getMovement()
        {
            if(IsKeyDown('W') || IsKeyDown(265))
            {
                pos.y -= speed;
            }
            else if(IsKeyDown('S') || IsKeyDown(264))
            {
                pos.y += speed;
            }
            else if(IsKeyDown('A') || IsKeyDown(263))
            {
                pos.x -= speed;
            }
            else if(IsKeyDown('D') ||IsKeyDown(262))
            {
                pos.x += speed;
            }

            //border collision checking
            if(pos.x <= 0)
            {
                pos.x = 0;
            }
            else if(pos.x >= GetScreenWidth()-width)
            {
                pos.x = GetScreenWidth()-width;
            }
            if(pos.y <= 0)
            {
                pos.y = 0;
            }
            else if(pos.y >= GetScreenHeight() - height)
            {
                pos.y = GetScreenHeight() - height;
            }
        }


        void checkForCollisions(std::vector<Rectangle> rects)
        {
            for(auto rect : rects)
            {
                checkCollision(rect);
            }
        }

        //resolve collisions with one rectangle
        void checkCollision(Rectangle rect)
        {
            //side = 0 no collision
            //side = 1 top
            //side = 2 right
            //side = 3 bottom
            //side = 4 left
            int side = 0;

            //top check
            if(pos.y + height > rect.y && pos.y < rect.y + rect.height)
            {
                if(pos.x + width > rect.x && pos.x + width < rect.x + rect.width)
                {
                    side = 1;
                }
                else if(pos.x < rect.x + rect.width && pos.x > rect.x)
                {
                    side = 1;
                }
                else if(pos.x > rect.x && pos.x + width < rect.x + rect.width)
                {
                    side = 1;
                }
            }

            //bottom check
            if(pos.y + height > rect.y + height && pos.y < rect.y + rect.height)
            {
                if(pos.x + width > rect.x && pos.x + width < rect.x + rect.width)
                {
                    side = 3;
                }
                else if(pos.x < rect.x + rect.width && pos.x > rect.x)
                {
                    side = 3;
                }
                else if(pos.x > rect.x && pos.x + width < rect.x + rect.width)
                {
                    side = 3;
                }
            }

            //right check
            if(pos.x < rect.x + rect.width && pos.x + width > rect.x + rect.width)
            {
                if(pos.y + height > rect.y && pos.y + height < rect.y + rect.height)
                {
                    side = 2;
                }
                else if(pos.y < rect.y + rect.height && pos.y > rect.y)
                {
                    side = 2;
                }
                else if(pos.y > rect.y && pos.y + height < rect.y + rect.height)
                {
                    side = 2;
                }
            }

            //left check
            if(pos.x + width > rect.x && pos.x < rect.x)
            {
                if(pos.y + height > rect.y && pos.y + height < rect.y + rect.height)
                {
                    side = 4;
                }
                else if(pos.y < rect.y + rect.height && pos.y > rect.y)
                {
                    side = 4;
                }
                else if(pos.y > rect.y && pos.y + height < rect.y + rect.height)
                {
                    side = 4;
                }
            }

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
};
