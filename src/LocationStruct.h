#ifndef LOCATION_STRUCT_H
#define LOCATION_STRUCT_H

#include <MovementStruct.h>
#include <raylib.h>
#include <string>

namespace testgame
{

struct LocationStruct
{
    Texture2D locationImage;
    std::string locationDescription;
    Font descriptionFont;
    MovementStruct movementFilter;
    // bool forward;
    // bool backward;
    // bool left;
    // bool right;
};

}

#endif /* LOCATION_STRUCT_H */