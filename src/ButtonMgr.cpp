#include "Button.h"
#include "ButtonMgr.h"
#include <raylib.h>
#include <vector>

namespace testgame
{

ButtonMgr::ButtonMgr(Rectangle _buttonBox, Font _buttonFont)
    : buttonBox(_buttonBox),
      buttonFont(_buttonFont)
{
    // TODO:  Note to self: the border is throwing off the button placement.  Don't care at the moment.

    // TODO: use a std::pair to like pointer functions for now
    
    buttons.push_back(Button("Foreward",
            {buttonBox.x + 110, buttonBox.y + 10},
            {buttonBox.width / 6.5f, buttonBox.height / 7.0f},
            buttonFont,
            WHITE,
            GRAY));

    buttons.push_back(Button("Backward",
            {buttonBox.x + 110, buttonBox.y + 70},
            {buttonBox.width / 6.5f, buttonBox.height / 7.0f},
            buttonFont,
            WHITE,
            GRAY));

    buttons.push_back(Button("Left",
        {buttonBox.x + 10, buttonBox.y + 10},
        {buttonBox.width / 8.0f, buttonBox.height / 3.275f},
        buttonFont,
        WHITE,
        GRAY));

    buttons.push_back(Button("Right",
        {buttonBox.x + 20 + buttonBox.width / 6.5f + buttonBox.width / 8.0f, buttonBox.y + 10},
        {buttonBox.width / 8.0f, buttonBox.height / 3.275f},
        buttonFont,
        WHITE,
        GRAY));

    buttons.push_back(Button("Examine",
        {buttonBox.x + buttonBox.width - 10 - buttonBox.width / 6, buttonBox.y + 10},
        {buttonBox.width / 6.0f, buttonBox.height / 7.0f},
        buttonFont,
        WHITE,
        GRAY));

    buttons.push_back(Button("Speak",
        {buttonBox.x + buttonBox.width - 10 - buttonBox.width / 6, buttonBox.y + 10 + buttonBox.height / 7.0f + 10},
        {buttonBox.width / 6.0f, buttonBox.height / 7.0f},
        buttonFont,
        WHITE,
        GRAY));


}


ButtonMgr::~ButtonMgr()
{
}

void ButtonMgr::update()
{
    Vector2 mousePos = GetMousePosition();
    for (auto& button : buttons)
    {
        if (CheckCollisionPointRec(mousePos, button.getBounds()))
        {
            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
                button.setState(PRESSED);
            else
                button.setState(HOVERED);
        }
        else
        {
            button.setState(NORMAL);
        }
    }
}

void ButtonMgr::draw() const
{
    DrawRectangleLinesEx(buttonBox, 4, GRAY);
    for (const auto& button : buttons)
        button.draw();
}

}
