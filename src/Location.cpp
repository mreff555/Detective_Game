#include <Location.h>
#include <raylib.h>

namespace testgame
{
    Location::Location(const LocationStruct& locationStruct, Vector2 screenSize)
    : locationImage(locationStruct.locationImage),
      locationDescription(locationStruct.locationDescription),
      descriptionFont(locationStruct.descriptionFont),
      forward(locationStruct.forward),
      backward(locationStruct.backward),
      left(locationStruct.left),
      right(locationStruct.right),
      screenWidth(screenSize.x),
      screenHeight(screenSize.y)
    {

    }

    Location::~Location()
    {
        UnloadTexture(locationImage);
    }

    const Texture2D Location::getImage() const
    {
        return locationImage;
    }
    const char* Location::getDescription() const
    {
        return locationDescription;
    }
    const Font Location::getFont() const
    {
        return descriptionFont;
    }
    const bool Location::isForward() const
    {
        return forward;
    }
    const bool Location::isBackward() const
    {
        return backward;
    }
    const bool Location::isLeft() const
    {
        return left;
    }
    const bool Location::isRight() const
    {
        return right;
    }
    void Location::draw() const
    {
        DrawTexture(locationImage, 0, 0, WHITE);
    }

}