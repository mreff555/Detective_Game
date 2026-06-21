#ifndef DROP_CONFIRM_MGR_H
#define DROP_CONFIRM_MGR_H

#include <Button.h>
#include <raylib.h>
#include <string>

namespace testgame
{

class DropConfirmMgr
{
    public:
    DropConfirmMgr(int screenWidth, int screenHeight, Font uiFont);

    void setScreenSize(int width, int height);

    bool isOpen() const { return open; }
    const std::string& getPendingItemId() const { return pendingItemId; }

    void openForItem(const std::string& itemId, const std::string& itemName);
    void close();

    void update();
    void draw() const;

    std::string consumeConfirmedItemId();
    bool consumeCancelled();
    bool consumeDontShowAgainRequest();

    private:
    void layoutButtons();
    Rectangle getPanelBounds() const;
    Rectangle getCheckboxBounds() const;
    void drawPanelFrame() const;
    void drawCheckbox() const;
    void handleCheckboxInput();

    int screenWidth;
    int screenHeight;
    Font uiFont;
    ButtonStyle buttonStyle{};

    bool open = false;
    std::string pendingItemId;
    std::string pendingItemName;
    bool dontShowAgainChecked = false;
    std::string confirmedItemId;
    bool cancelled = false;
    bool dontShowAgainRequested = false;

    Button yesButton;
    Button noButton;
};

}

#endif /* DROP_CONFIRM_MGR_H */