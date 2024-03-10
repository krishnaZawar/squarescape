#include<vector>
#include "raylib.h"

class levelFinisher
{
    //border
    float border;
    Color borderColor;

    //inner filling
    float inner_width;
    float inner_height;
    Vector2 inner_pos;

    public:
        Vector2 pos;
        float width;
        float height;

        void defaultSettings()
        {
            border = 5;
            width = height = 20;
            inner_height = inner_width = width - 2*border;
            borderColor = BLACK;
        }

        levelFinisher(){}

        levelFinisher(int posX, int posY)
        {
            pos.x = posX;
            pos.y = posY;
            defaultSettings();
            inner_pos = {posX+border, posY+border};
        }
        
        void Draw()
        {
            DrawRectangleV(pos, {width, height},borderColor);
            DrawRectangleV(inner_pos, {inner_width, inner_height}, WHITE);
        }
};