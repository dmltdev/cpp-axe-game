#include "raylib.h"
#include <stdio.h>

int main() 
{
    int width{350};
    int height{200};
    InitWindow(width, height, "Axe Game");

   /* The lines `int circle_x{width/2};` and `int circle_y{height/2};` are initializing the variables
   `circle_x` and `circle_y` with the half of the `width` and `height` respectively. This positions
   the circle at the center of the window initially. */
    int circle_x{width/2};
    int circle_y{height/2};

    SetTargetFPS(60);
    while (!WindowShouldClose()) 
    {
        BeginDrawing();
        ClearBackground(WHITE);

        DrawCircle(circle_x, circle_y, 25, BLUE);

        if (IsKeyDown(KEY_D) && circle_x < width)
        {
            circle_x = circle_x + 10;
        }
        if (IsKeyDown(KEY_A) && circle_x > 0)
        {
            circle_x = circle_x - 10;
        }

        EndDrawing();
    }
}