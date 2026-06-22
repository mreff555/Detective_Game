#ifndef TAKE_MGR_H
#define TAKE_MGR_H

#include <TakeableItemDef.h>
#include <UiBackdrop.h>
#include <raylib.h>
#include <string>
#include <vector>

namespace testgame
{

struct TakeSlot
{
    TakeableItemDef def;
    Texture2D icon{};
    bool ownsIcon = false;
};

class TakeMgr
{
    public:
    TakeMgr();
    ~TakeMgr();

    void setPanelBounds(Rectangle bounds);
    void setFont(Font font);
    void setAssetRoots(const std::string& primaryAssetRoot, const std::string& fallbackAssetRoot);
    void setUiBackdrop(const UiBackdrop* backdrop);

    bool isOpen() const { return openState; }
    void open();
    void close();

    void setAvailableItems(const std::vector<TakeableItemDef>& items);
    bool isEmpty() const { return slots.empty(); }

    bool tryTakeItem(const std::string& id, TakeableItemDef& outTaken);
    std::vector<TakeableItemDef> takeAll();

    bool hasPendingTake() const { return !pendingTakeId.empty(); }
    std::string consumePendingTakeId();
    bool consumePendingTakeAll();

    void update();
    void draw() const;

    private:
    void clearSlots();
    bool loadSlotIcon(TakeSlot& slot);
    bool loadIconTexture(const std::string& relativePath, Texture2D& outTexture) const;
    Texture2D createPlaceholderIcon(const std::string& label) const;
    void drawCloseButton() const;
    void drawItemGrid() const;
    void drawTakeAllButton() const;
    void handleCloseButtonInput();
    void handleItemGridInput();
    void handleTakeAllButtonInput();
    void layoutItemSlots();
    Rectangle getCloseButtonBounds() const;
    Rectangle getTakeAllButtonBounds() const;
    float getContentAreaHeight() const;

    static const float kCloseButtonSize;
    static const float kItemSlotSize;
    static const float kItemGap;
    static const float kTakeAllButtonHeight;

    Font panelFont{};
    Rectangle panelBounds{};
    bool openState = false;
    std::vector<TakeSlot> slots;
    mutable std::vector<Rectangle> itemSlotBounds;
    std::string primaryAssetRoot;
    std::string fallbackAssetRoot;
    const UiBackdrop* uiBackdrop = nullptr;
    std::string pendingTakeId;
    bool pendingTakeAll = false;
};

}

#endif /* TAKE_MGR_H */