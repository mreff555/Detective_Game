#ifndef LOCATION_H
#define LOCATION_H

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

class Location
{
    public:
    Location(const LocationStruct& locationStruct, Vector2 screenSize);

    virtual ~Location();

    const Texture2D getImage() const;
    const char* getDescription() const;
    const Font getFont() const;
    const bool isForward() const;
    const bool isBackward() const;
    const bool isLeft() const;
    const bool isRight() const;

    void draw() const;

    private:
    const Texture2D locationImage;
    const char* locationDescription;
    const Font descriptionFont;
    const bool forward;
    const bool backward;
    const bool left;
    const bool right;

    const int screenWidth;
    const int screenHeight;
    // TODO: class for observations and items
};

}

#endif /* LOCATION_H */
