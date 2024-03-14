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

    public:
        levelFinisher()
        {
            border = 5;
            width = height = 20;
            inner_height = inner_width = width - 2*border;
        }
        
        void Draw()
        {
            DrawRectangleV(pos, {width, height}, BLACK);
            DrawRectangleV(inner_pos, {inner_width, inner_height}, YELLOW);
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