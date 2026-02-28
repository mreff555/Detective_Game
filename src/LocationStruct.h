#ifndef LOCATION_STRUCT_H
#define LOCATION_STRUCT_H

#include <raylib.h>
namespace testgame
{

struct LocationStruct
{
    const Texture2D locationImage;
    const char* locationDescription;
    const Font descriptionFont;
    const bool forward;
    const bool backward;
    const bool left;
    const bool right;
};

}

#endif /* LOCATION_STRUCT_H */