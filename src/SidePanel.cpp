#include "SidePanel.h"

#include <ImageCompression.h>
#include <RaylibCompat.h>

namespace highline_ridge
{

namespace
{
    const Color kPanelFill = {28, 26, 34, 255};
    const Color kPanelBorder = {168, 138, 72, 255};
    const Color kPanelAccent = {96, 78, 48, 255};
    const Color kSectionLabel = {132, 122, 104, 255};
}

void SidePanelChrome::drawPanelBackground(Rectangle bounds)
{
    DrawRectangleRounded(bounds, 0.04f, 10, kPanelFill);
    DrawRoundedBorder(bounds, 0.04f, 10, 3.0f, kPanelBorder);

    const Rectangle accentBar = {
        bounds.x + 8.0f,
        bounds.y + 8.0f,
        bounds.width - 16.0f,
        4.0f
    };
    DrawRectangleRounded(accentBar, 1.0f, 4, kPanelAccent);
}

void SidePanelChrome::drawPanelHeader(Font font, Rectangle bounds, const char* title)
{
    const float pad = 14.0f;
    DrawTextEx(font, title, { bounds.x + pad, bounds.y + pad }, 17.0f, 1, kSectionLabel);
}

Rectangle SidePanelChrome::getCloseButtonBounds(Rectangle panelBounds, float closeButtonSize)
{
    const float pad = 14.0f;
    return {
        panelBounds.x + panelBounds.width - closeButtonSize - pad,
        panelBounds.y + pad,
        closeButtonSize,
        closeButtonSize
    };
}

bool SidePanelChrome::loadIconTexture(
    const std::string& primaryAssetRoot,
    const std::string& fallbackAssetRoot,
    const std::string& relativePath,
    Texture2D& outTexture)
{
    if (relativePath.empty())
        return false;

    const std::string primaryPath = primaryAssetRoot + "/" + relativePath;
    const std::string fallbackPath = fallbackAssetRoot + "/" + relativePath;

    if (loadTextureFromAssetFile(primaryPath, outTexture))
        return true;

    if (loadTextureFromAssetFile(fallbackPath, outTexture))
        return true;

    return false;
}

}