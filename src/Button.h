#ifndef BUTTON_H
#define BUTTON_H

#include <raylib.h>

enum ButtonState
{
    NORMAL,
    HOVERED,
    PRESSED
};

class Button
{
    public:
    Button(const char* text, Vector2 position, Vector2 size, Font font, Color textColor, Color backgroundColor);
    virtual ~Button();

    void draw() const;
    bool isClicked() const;
    Rectangle getBounds() const;
    void setState(ButtonState state);

    private:
    const char* text;
    Vector2 position;
    Vector2 size;
    Font font;
    Color textColor;
    Color backgroundColor;
    ButtonState state = NORMAL;
};

#endif /* BUTTON_H */

