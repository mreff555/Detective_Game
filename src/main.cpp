#include <Location.h>
#include <raylib.h>
#include <stdio.h>

using namespace testgame;

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const Vector2 screenSize = {1500, 1117};
    InitWindow(screenSize.x, screenSize.y, "raylib test game");
    
    LocationStruct locationStruct = {
        LoadTexture("../resources/cabin.png"),
        "In a dimly lit cabin, an old man sits by the fire surrounded by surprisingly lavish furnishings, given the condition of the cabin.",
        LoadFont("/System/Library/Fonts/Geneva.ttf"),
        false,
        true,
        false,
        false};
    
    Location location(locationStruct, screenSize);

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // if (IsKeyDown(KEY_RIGHT)) ballPosition.x += 2.0f;
        // if (IsKeyDown(KEY_D)) ballPosition.x += 2.0f;
        // if (IsKeyDown(KEY_LEFT)) ballPosition.x -= 2.0f;
        // if (IsKeyDown(KEY_A)) ballPosition.x -= 2.0f;
        // if (IsKeyDown(KEY_UP)) ballPosition.y -= 2.0f;
        // if (IsKeyDown(KEY_W)) ballPosition.y -= 2.0f;
        // if (IsKeyDown(KEY_DOWN)) ballPosition.y += 2.0f;
        // if (IsKeyDown(KEY_S)) ballPosition.y += 2.0f;
        // if (IsKeyDown(KEY_R)) ballRadius += 1.0f;
        // if (IsKeyDown(KEY_F)) ballRadius -= 1.0f;

        // if(ballPosition.x <= 0) ballPosition.x = (float)screenWidth;
        // else if(ballPosition.x >= screenWidth) ballPosition.x = 0;
        // if(ballPosition.y <= 0) ballPosition.y = (float)screenHeight;
        // else if(ballPosition.y >= screenHeight) ballPosition.y = 0;

        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(BLACK);

            location.draw();

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
