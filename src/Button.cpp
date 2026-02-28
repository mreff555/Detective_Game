#include <Button.h>
#include <raylib.h>

Button::Button(const char* text, Vector2 position, Vector2 size, Font font, Color textColor, Color backgroundColor)
    : text(text), position(position), size(size), font(font), textColor(textColor), backgroundColor(backgroundColor)
{
}

Button::~Button()
{
}

void Button::draw() const
{
    DrawRectangleV(position, size, backgroundColor);
    Vector2 textSize = MeasureTextEx(font, text, font.baseSize, 0);
    Vector2 textPosition = { position.x + (size.x - textSize.x) / 2, position.y + (size.y - textSize.y) / 2 };
    DrawTextEx(font, text, textPosition, font.baseSize, 0, textColor);
}

bool Button::isClicked() const
{
    return IsMouseButtonPressed(MOUSE_LEFT_BUTTON) &&
           CheckCollisionPointRec(GetMousePosition(), { position.x, position.y, size.x, size.y });
}
