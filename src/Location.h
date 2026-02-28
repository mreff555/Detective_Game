#ifndef LOCATION_H
#define LOCATION_H

#include <raylib.h>
#include <LocationStruct.h>
#include <string>
namespace testgame
{

class Location
{
    public:
    Location(const LocationStruct& locationStruct, Vector2 screenSize);

    virtual ~Location();

    Texture2D getImage() const;
     char* getDescription() const;
    const Font getDescriptionFont() const;
    bool isForward() const;
    bool isBackward() const;
    bool isLeft() const;
    bool isRight() const;

    void draw() const;
    void update(const LocationStruct& locationStruct);
    void DrawTextBoxed(const char* text) const;

    private:
    const int screenWidth;
    const int screenHeight;
    
    Texture2D locationImage;
    std::string locationDescription;
    Font descriptionFont;
    
    bool forward;
    bool backward;
    bool left;
    bool right;

    float fontSize = 20;
    const bool wordWrap = true;
    const int spacing = 2;
    const Color textColor = DARKGRAY;
    const int xOffset = 14;
    const int yOffset = 14;

    const Rectangle textBox;

    // TODO: class for observations and items
};

}

#endif /* LOCATION_H */
