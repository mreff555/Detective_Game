#include "ModalPanel.h"

#include <RaylibCompat.h>

namespace highline_ridge
{

namespace
{
    const ModalPanelStyle kDefaultStyle = {
        {8, 8, 12, 210},
        {28, 26, 34, 255},
        {168, 138, 72, 255},
        {96, 78, 48, 255},
        {228, 220, 198, 255}
    };
}

ModalPanel::ModalPanel()
{
}

ModalPanel::ModalPanel(int screenWidth_, int screenHeight_)
    : screenWidth(screenWidth_),
      screenHeight(screenHeight_)
{
}

void ModalPanel::setScreenSize(int width, int height)
{
    screenWidth = width;
    screenHeight = height;
}

const ModalPanelStyle& ModalPanel::defaultStyle()
{
    return kDefaultStyle;
}

void ModalPanel::drawOverlay() const
{
    DrawRectangle(0, 0, screenWidth, screenHeight, kDefaultStyle.overlayDim);
}

void ModalPanel::drawChrome(const Rectangle& panel) const
{
    DrawRectangleRounded(panel, 0.05f, 12, kDefaultStyle.panelFill);
    DrawRoundedBorder(panel, 0.05f, 12, 3.0f, kDefaultStyle.panelBorder);

    const Rectangle accentBar = {
        panel.x + 12.0f,
        panel.y + 12.0f,
        panel.width - 24.0f,
        4.0f
    };
    DrawRectangleRounded(accentBar, 1.0f, 4, kDefaultStyle.panelAccent);
}

void ModalPanel::drawCenteredTitle(
    Font font,
    const Rectangle& panel,
    const char* title,
    float fontSize) const
{
    const Vector2 titleSize = MeasureTextEx(font, title, fontSize, 1);
    DrawTextEx(
        font,
        title,
        {
            panel.x + (panel.width - titleSize.x) * 0.5f,
            panel.y + 34.0f
        },
        fontSize,
        1,
        kDefaultStyle.titleColor);
}

}