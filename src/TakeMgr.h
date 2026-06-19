#ifndef TAKE_MGR_H
#define TAKE_MGR_H

#include <TakeableItem.h>
#include <raylib.h>
#include <string>
#include <vector>

namespace testgame
{

class TakeMgr
{
    public:
    TakeMgr();
    ~TakeMgr();

    void setPanelBounds(Rectangle bounds);
    void setFont(Font font);
    void setAssetRoots(const std::string& primaryRoot, const std::string& fallbackRoot);
    void setTakeables(const std::vector<TakeableItem>& takeables);

    bool isOpen() const { return isPanelOpen; }

    void open();
    void close();
    void removeTakeable(const std::string& id);
    bool hasTakeables() const { return !items.empty(); }

    void update();
    void draw() const;

    std::string consumeClickedItemId();
    bool consumeTakeAllClick();

    private:
    void unloadItemTextures();
    void loadItemTextures();
    bool loadItemTexture(const std::string& relativePath, Texture2D& outTexture) const;
    void drawCloseButton() const;
    void drawItemGrid() const;
    void drawTakeAllButton() const;
    void handleItemGridInput();
    void handleTakeAllInput();
    void handleCloseButtonInput();
    void handleScrollInput();
    void drawScrollbar() const;
    void layoutItemSlots();
    Rectangle getCloseButtonBounds() const;
    Rectangle getTakeAllButtonBounds() const;
    float getContentVisibleHeight() const;

    static const float kScrollbarWidth;
    static const float kCloseButtonSize;
    static const float kItemSlotSize;
    static const float kItemGap;
    static const float kTakeAllButtonHeight;

    Font panelFont{};
    Rectangle panelBounds{};
    bool isPanelOpen = false;
    std::vector<TakeableItem> items;
    mutable std::vector<Rectangle> itemSlotBounds;
    std::string primaryAssetRoot;
    std::string fallbackAssetRoot;

    std::string clickedItemId;
    bool takeAllClicked = false;

    float scrollY = 0.0f;
    float contentHeight = 0.0f;
    bool scrollbarDragging = false;
    float scrollbarDragOffsetY = 0.0f;
};

}

#endif /* TAKE_MGR_H */