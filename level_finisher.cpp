#include<vector>
#include "raylib.h"

class levelFinisher
{
    //border
    float border;
    Vector2 pos;
    float width;
    float height;

    //inner filling
    float inner_width;
    float inner_height;
    Vector2 inner_pos;

    //blinking anim vars
    float opacity;
    bool fading;

    //colors
    Color black;
    Color yellow;

    public:
        levelFinisher()
        {
            black = Color(BLACK.r, BLACK.g, BLACK.b, BLACK.a);
            yellow = Color(YELLOW.r, YELLOW.g, YELLOW.b, YELLOW.a);
            opacity = 1;
            fading = true;
            border = 5;
            width = height = 20;
            inner_height = inner_width = width - 2*border;
        }
        
        void Draw()
        {
            //changing opacity of the colors to create a blinking animation 

            float deltaTime = (1.0/GetFPS()) * 0.75;

            if(opacity <= 0.3)
            {
                fading = false;
            }
            else if(opacity >= 0.9) 
            {
                fading = true;
            }

            if(fading) opacity -= deltaTime;
            else opacity += deltaTime;

            black.a = yellow.a = 255*opacity;
            
            DrawRectangleV(pos, {width, height}, black);
            DrawRectangleV(inner_pos, {inner_width, inner_height}, yellow);
        }

        void setPos(Vector2 pos)
        {
            this->pos = pos;
            inner_pos = {this->pos.x+border, this->pos.y+border};
        }

        Vector2 getPos()
        {
            return pos;
        }
        
        int getWidth()
        {
            return width;
        }
        int getHeight()
        {
            return height;
        }
};