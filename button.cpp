#include "raylib.h"

#include<string>

class Button
{   
    std::string place_holder;
    int width;
    int height;
    Texture2D border;

    Vector2 pos;

    Color fill;

    public:
        Button() {}

        Button(std::string place_holder)
        {
            fill = WHITE;
            border = LoadTexture("resources/button_border.png");
            this->place_holder = place_holder;
            width = 210;
            height = 60;
        }

        void Draw(Vector2 pos, Vector2 place_holder_pos)
        {
            this->pos = Vector2(pos.x + 6, pos.y + 6);
            DrawRectangleV(this->pos, Vector2(width, height), fill);
            DrawTextureV(border, pos, fill);
            DrawText(place_holder.c_str(), place_holder_pos.x, place_holder_pos.y, 30, BLACK);
        }

        bool isClicked()
        {
            Vector2 mousePos = Vector2(GetMouseX(), GetMouseY());

            return CheckCollisionPointRec(mousePos, Rectangle(pos.x, pos.y, width, height));
        }

        void onHover()
        {
            Vector2 mousePos = Vector2(GetMouseX(), GetMouseY());

            if(CheckCollisionPointRec(mousePos, Rectangle(pos.x, pos.y, width, height)))
            {
                fill = GRAY;
            }
            else
            {
                fill = WHITE;
            }
        }
};