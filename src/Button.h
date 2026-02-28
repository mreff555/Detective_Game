#ifndef BUTTON_H
#define BUTTON_H

#include <raylib.h>

class Button
{
    public:
    Button(const char* text, Vector2 position, Vector2 size, Font font, Color textColor, Color backgroundColor);
    virtual ~Button();

    void draw() const;
    bool isClicked() const;

    private:
    const char* text;
    Vector2 position;
    Vector2 size;
    Font font;
    Color textColor;
    Color backgroundColor;
};

#endif /* BUTTON_H */
