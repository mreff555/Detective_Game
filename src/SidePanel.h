#ifndef SIDE_PANEL_H
#define SIDE_PANEL_H

#include <raylib.h>
#include <string>

namespace testgame
{

struct SidePanelChrome
{
    static void drawPanelBackground(Rectangle bounds);
    static void drawPanelHeader(Font font, Rectangle bounds, const char* title);
    static Rectangle getCloseButtonBounds(Rectangle panelBounds, float closeButtonSize);
    static bool loadIconTexture(
        const std::string& primaryAssetRoot,
        const std::string& fallbackAssetRoot,
        const std::string& relativePath,
        Texture2D& outTexture);
};

}

#endif /* SIDE_PANEL_H */