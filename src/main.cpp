#include <Location.h>
#include <RoomLoader.h>
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

    LocationStruct locationStruct;
    if (!loadStartLocation("../resources/rooms.json", "..", locationStruct))
    {
        TraceLog(LOG_ERROR, "Failed to load starting room from resources/rooms.json");
        CloseWindow();
        return 1;
    }

    Location location(locationStruct, screenSize);

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        location.update();
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

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