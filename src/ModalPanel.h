#ifndef MODAL_PANEL_H
#define MODAL_PANEL_H

#include <raylib.h>

namespace testgame
{

struct ModalPanelStyle
{
    Color overlayDim;
    Color panelFill;
    Color panelBorder;
    Color panelAccent;
    Color titleColor;
};

class ModalPanel
{
    public:
    ModalPanel();
    ModalPanel(int screenWidth, int screenHeight);

    void setScreenSize(int width, int height);
    void drawOverlay() const;
    void drawChrome(const Rectangle& panel) const;
    void drawCenteredTitle(
        Font font,
        const Rectangle& panel,
        const char* title,
        float fontSize = 24.0f) const;

    static const ModalPanelStyle& defaultStyle();

    private:
    int screenWidth = 0;
    int screenHeight = 0;
};

}

#endif /* MODAL_PANEL_H */