#ifndef LOCATION_H
#define LOCATION_H

#include <raylib.h>
#include <LocationStruct.h>

namespace testgame
{

class Location
{
    public:
    Location(const LocationStruct& locationStruct, Vector2 screenSize);

    virtual ~Location();

    const Texture2D getImage() const;
    const char* getDescription() const;
    const Font getDescriptionFont() const;
    const bool isForward() const;
    const bool isBackward() const;
    const bool isLeft() const;
    const bool isRight() const;

    void draw() const;
    void DrawTextBoxed(const char* text) const;

    private:
    const int screenWidth;
    const int screenHeight;
    
    const Texture2D locationImage;

    const char* locationDescription;
    const Font descriptionFont;
    const float fontSize = 20;
    const bool wordWrap = true;
    const int spacing = 2;
    const Color textColor = DARKGRAY;
    const int xOffset = 14;
    const int yOffset = 14;

    const bool forward;
    const bool backward;
    const bool left;
    const bool right;

    const Rectangle textBox;

    // TODO: class for observations and items
};

}

#endif /* LOCATION_H */
