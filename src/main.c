#include "raylib.h"
#include "rcamera.h"
#include "map.h"
#include "fncs.h"

#define SCREEN_X 900
#define SCREEN_Y 600

#define SIZE 32
#define GRID 2

struct collect
{
    bool active;
    Vector3 position;
};

// MAIN
int main(void)
{
    // INITIALIZATION
    int score = 0;

    // WINDOW
    InitWindow(SCREEN_X, SCREEN_Y, "raycaster");

    // CAMERA
    Camera camera = { 0 };
    camera.position = (Vector3){ 16.0f, 2.0f, 16.0f };
    camera.target = (Vector3){ 0.0f, 2.0f, 0.0f };
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy = 60.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    int camera_mode = CAMERA_FIRST_PERSON;

    // GROUND
    Vector3 ground_position = { 16.0f, -0.5f, 16.0f };

    // COLLECT
    struct collect one;
    Vector3 tmp1 = {4.0f, 2.0f, 4.0f};
    one.position = tmp1;
    one.active = true;

    struct collect two;
    Vector3 tmp2 = {22.0f, 2.0f, 12.0f};
    two.position = tmp2;
    two.active = true;

    SetTargetFPS(90);
    DisableCursor();

    // MAIN LOOP
    while (!WindowShouldClose())
    {
        // UPDATE | TODO:
        UpdateCamera(&camera, camera_mode);

        // DRAW
        BeginDrawing();

        ClearBackground(BLACK);

        // CAMERA
        BeginMode3D(camera);

        // CUBE
        DrawCube(ground_position, 32.0f, 1.0f, 32.0f, BLACK);

        // MAP
        for (int x = 0; x < SIZE; ++x)
        {
            for (int y = 0; y < SIZE; ++y)
            {
                int temp = map[x][y];

                if (x != 16 && y != 16)
                {
                    if (temp == 1)
                    {
                        Vector3 pos = {(float)x * 2, 1, (float)y * 2};
                        DrawCube(pos, 2.0f, 5.0f, 2.0f, RED);
                        DrawCubeWires(pos, 2.0f, 5.0f, 2.0f, BLACK);
                    }

                    if (temp == 2)
                    {
                        Vector3 pos = {(float)x * 2, 2, (float)y * 2};
                        DrawCube(pos, 2.0f, 5.0f, 2.0f, GREEN);
                        DrawCubeWires(pos, 2.0f, 5.0f, 2.0f, BLACK);
                    }

                    if (temp == 3)
                    {
                        Vector3 pos = {(float)x * 2, 2, (float)y * 2};
                        DrawCube(pos, 2.0f, 5.0f, 2.0f, BLUE);
                        DrawCubeWires(pos, 2.0f, 5.0f, 2.0f, BLACK);
                    }

                    if (temp == 4)
                    {
                        Vector3 pos = {(float)x * 2, 1, (float)y * 2};
                        DrawCube(pos, 2.0f, 2.0f, 2.0f, PINK);
                        DrawCubeWires(pos, 2.0f, 2.0f, 2.0f, BLACK);
                    }

                    if (temp == 5)
                    {
                        Vector3 pos = {(float)x * 2, 2, (float)y * 2};
                        DrawCube(pos, 1.0f, 1.0f, 1.0f, YELLOW);
                        DrawCubeWires(pos, 1.0f, 1.0f, 1.0f, BLACK);
                    }
                }
            }
        }

        if (distance(camera.position, one.position) < 1.5f && one.active)
        {
            score += 1;
            one.active = false;
        }
        if (one.active)
        {
            DrawCube(one.position, 1.0f, 1.0f, 1.0f, YELLOW);
            DrawCubeWires(one.position, 1.0f, 1.0f, 1.0f, WHITE);
        }

        if (distance(camera.position, two.position) < 1.5f && two.active)
        {
            score += 1;
            two.active = false;
        }
        if (two.active)
        {
            DrawCube(two.position, 1.0f, 1.0f, 1.0f, YELLOW);
            DrawCubeWires(two.position, 1.0f, 1.0f, 1.0f, WHITE);
        }

        EndMode3D();

        // TEXT
        char conv[10];
        snprintf(conv, sizeof(conv), "%d", score);

        DrawText("SCORE: ", 10, 40, 20, LIGHTGRAY);
        DrawText(conv, 90, 40, 20, LIGHTGRAY);

        DrawText("FPS: ", 10, 10, 20, GREEN);
        DrawFPS(60, 10);

        if (score >= 2)
        {
            DrawText("CONGRATULATIONS! \nYOU HAVE COLLECTED EVERYTHING \nPRESS ESC TO QUIT", 20, 500, 20, LIGHTGRAY);
        }

        EndDrawing();
    }

    // DE-INITIALIZATION
    CloseWindow();

    return 0;
}