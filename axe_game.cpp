#include "raylib.h"
#include <stdio.h>
#include <iostream>

void DrawCirclePlayer(int x, int y, int radius);
void DrawAxe(int x, int y, int length);
bool CheckCollision(int circle_x, int circle_y, int circle_radius, int axe_x, int axe_y, int axe_length);
void UpdateAxeMovement(int& axe_y, int& axe_direction, int window_h);
void UpdateCircleMovement(int& circle_x, int& circle_y, int window_w, int window_h);
bool IsRestartButtonPressed(int window_w, int window_h);

int main() 
{
    // window 
    int window_w{800};
    int window_h{450};
    InitWindow(window_w, window_h, "Axe Game");
    SetTargetFPS(60);

    // circle params
    int circle_x{200};
    int circle_y{200};
    int circle_radius{25};

    // axe params
    int axe_x{400};
    int axe_y{0};
    int axe_length{50};
    int axe_direction{10};

    bool game_over = false;

    // Game Logic
    while (!WindowShouldClose()) 
    {
        // Background
        BeginDrawing();
        ClearBackground(WHITE);

        if (game_over)
        {
            // Draw "Game Over" text
            DrawText("Game Over!", window_w/2 - 60, window_h/2 - 20, 20, RED);

            // Draw Restart Button
            DrawRectangle(window_w/2 - 60, window_h/2 + 40, 120, 40, DARKGRAY);
            DrawText("RESTART", window_w/2 - 50, window_h/2 + 50, 20, WHITE);

            // Check for restart
            if (IsRestartButtonPressed(window_w, window_h))
            {
                // Reset game state
                circle_x = 200;
                circle_y = 200;
                axe_x = 400;
                axe_y = 0;
                game_over = false;
            }
        } 
        else 
        {
            // Check for collision
            bool collision_with_axe = CheckCollision(circle_x, circle_y, circle_radius, axe_x, axe_y, axe_length);

            if (collision_with_axe)
            {
                game_over = true;
            } 
            else 
            {
                // Draw objects
                DrawCirclePlayer(circle_x, circle_y, circle_radius);
                DrawAxe(axe_x, axe_y, axe_length);

                // Update movements
                UpdateAxeMovement(axe_y, axe_direction, window_h);
                UpdateCircleMovement(circle_x, circle_y, window_w, window_h);
            }
        }

        EndDrawing();
    }
}

void DrawCirclePlayer(int x, int y, int radius)
{
    DrawCircle(x, y, radius, BLUE);
}

void DrawAxe(int x, int y, int length)
{
    DrawRectangle(x, y, length, length, RED);
}

bool CheckCollision(int circle_x, int circle_y, int circle_radius, int axe_x, int axe_y, int axe_length)
{
    int l_circle_x = circle_x - circle_radius;
    int r_circle_x = circle_x + circle_radius;
    int u_circle_y = circle_y - circle_radius;
    int b_circle_y = circle_y + circle_radius;

    int l_axe_x = axe_x;
    int r_axe_x = axe_x + axe_length;
    int u_axe_y = axe_y;
    int b_axe_y = axe_y + axe_length;

    return b_axe_y >= u_circle_y && u_axe_y <= b_circle_y && r_axe_x >= l_circle_x && l_axe_x <= r_circle_x;
}

void UpdateAxeMovement(int& axe_y, int& axe_direction, int window_h)
{
    axe_y += axe_direction;
    if (axe_y > window_h || axe_y < 0)
    {
        axe_direction = -axe_direction;
    }
}

void UpdateCircleMovement(int& circle_x, int& circle_y, int window_w, int window_h)
{
    if (IsKeyDown(KEY_D) && circle_x < window_w)
    {
        circle_x += 10;
    }
    if (IsKeyDown(KEY_A) && circle_x > 0)
    {
        circle_x -= 10;
    }
    if (IsKeyDown(KEY_W) && circle_y > 0)
    {
        circle_y -= 10;
    }
    if (IsKeyDown(KEY_S) && circle_y < window_h)
    {
        circle_y += 10;
    }
}

bool IsRestartButtonPressed(int window_w, int window_h)
{
    if (IsKeyPressed(KEY_SPACE))
    {
        return true;
    }

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        Vector2 mouse_position = GetMousePosition();
        int button_x = window_w / 2 - 60;
        int button_y = window_h / 2 + 40;
        int button_width = 120;
        int button_height = 40;

        if (mouse_position.x >= button_x && mouse_position.x <= button_x + button_width &&
            mouse_position.y >= button_y && mouse_position.y <= button_y + button_height)
        {
            return true;
        }
    }

    return false;
}
