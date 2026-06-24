#ifndef SCROLL_PANEL_H
#define SCROLL_PANEL_H

#include <raylib.h>

namespace highline_ridge
{

class ScrollPanel
{
    public:
    static const float kDefaultScrollbarWidth;

    ScrollPanel();

    void setContentHeight(float height);
    void setVisibleArea(Rectangle area);
    void setScrollTrack(Rectangle track);
    void setWheelStep(float step);
    void setWheelMultiplier(float multiplier);
    void setWheelEnabled(bool enabled);
    void setInputBlocked(bool blocked);
    void setClampToBottom(bool clamp);

    void handleInput();
    void drawScrollbar() const;

    float getScrollY() const { return scrollY; }
    void setScrollY(float y);
    void resetScroll();
    float getMaxScroll() const;
    float getContentHeight() const { return contentHeight; }

    static void applyWheelScroll(
        float& scrollY,
        const Rectangle& wheelArea,
        float contentHeight,
        float visibleHeight,
        float wheelStep);

    private:
    float scrollY = 0.0f;
    float contentHeight = 0.0f;
    Rectangle visibleArea{};
    Rectangle scrollTrack{};
    float wheelStep = 24.0f;
    float wheelMultiplier = 1.0f;
    bool wheelEnabled = true;
    bool inputBlocked = false;
    bool clampToBottom = false;
    bool hasScrollTrack = false;
    bool scrollbarDragging = false;
    float scrollbarDragOffsetY = 0.0f;
};

}

#endif /* SCROLL_PANEL_H */