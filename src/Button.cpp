#include "Button.h"
#include <raylib.h>

Button::Button(const char* text, Vector2 position, Vector2 size, Font font, const ButtonStyle& style)
    : text(text), position(position), size(size), font(font), style(style)
{
}

Button::~Button()
{
}

void Button::draw() const
{
    Color fillColor = style.normalBg;
    if (state == HOVERED)
        fillColor = style.hoverBg;
    else if (state == PRESSED)
        fillColor = style.pressedBg;

    Rectangle bounds = getBounds();
    DrawRectangleRounded(bounds, style.roundness, 8, fillColor);
    DrawRectangleRoundedLines(bounds, style.roundness, 8, 2.0f, style.borderColor);

    if (state == HOVERED)
    {
        Rectangle highlight = { bounds.x + 2, bounds.y + 2, bounds.width - 4, bounds.height * 0.35f };
        DrawRectangleRounded(highlight, style.roundness, 8, Fade(WHITE, 0.08f));
    }

    Vector2 textSize = MeasureTextEx(font, text, style.fontSize, 1);
    Vector2 textPosition = {
        position.x + (size.x - textSize.x) / 2.0f,
        position.y + (size.y - textSize.y) / 2.0f
    };
    DrawTextEx(font, text, textPosition, style.fontSize, 1, style.textColor);
}

bool Button::isClicked() const
{
    return IsMouseButtonPressed(MOUSE_LEFT_BUTTON) &&
           CheckCollisionPointRec(GetMousePosition(), getBounds());
}

Rectangle Button::getBounds() const
{
    return { position.x, position.y, size.x, size.y };
}

void Button::setState(ButtonState state)
{
    this->state = state;
}