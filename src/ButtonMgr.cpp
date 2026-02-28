#include <Button.h>
#include <ButtonMgr.h>
#include <raylib.h>

namespace testgame
{

ButtonMgr::ButtonMgr(Rectangle _buttonBox, Font _buttonFont)
    : buttonBox(_buttonBox),
      buttonFont(_buttonFont)
{
}

ButtonMgr::~ButtonMgr()
{
}

void ButtonMgr::draw() const
{
        Button upButton(
            "Up",
            {buttonBox.x + 100, buttonBox.y + 10},
            {buttonBox.width / 4.0f, buttonBox.height / 4.0f},
            buttonFont,
            WHITE,
            GRAY);

    // Button Box
    DrawRectangleLinesEx(buttonBox, 4, GRAY);
    upButton.draw();
}

}
