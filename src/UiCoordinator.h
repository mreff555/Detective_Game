#ifndef UI_COORDINATOR_H
#define UI_COORDINATOR_H

namespace testgame
{

class DropConfirmMgr;
class InteractionMgr;
class InventoryMgr;
class PauseMenuMgr;
class SaveLoadMenuMgr;
class TakeMgr;

enum class UiMode
{
    Gameplay,
    Inventory,
    Take,
    Interact,
    DropConfirm,
    Pause,
    SaveLoad
};

class UiCoordinator
{
    public:
    UiMode getMode() const { return mode; }
    bool isGameplay() const { return mode == UiMode::Gameplay; }

    void open(UiMode newMode,
        InventoryMgr& inventoryMgr,
        TakeMgr& takeMgr,
        InteractionMgr& interactionMgr,
        DropConfirmMgr& dropConfirmMgr,
        PauseMenuMgr& pauseMenu,
        SaveLoadMenuMgr& saveLoadMenu);

    void openSaveMenu(SaveLoadMenuMgr& saveLoadMenu);
    void openLoadMenu(SaveLoadMenuMgr& saveLoadMenu);
    void openDropConfirm();

    void closeSaveLoadMenu(SaveLoadMenuMgr& saveLoadMenu, const PauseMenuMgr& pauseMenu);
    void closePauseMenu(PauseMenuMgr& pauseMenu, SaveLoadMenuMgr& saveLoadMenu);

    void closeAll(
        InventoryMgr& inventoryMgr,
        TakeMgr& takeMgr,
        InteractionMgr& interactionMgr,
        DropConfirmMgr& dropConfirmMgr,
        PauseMenuMgr& pauseMenu,
        SaveLoadMenuMgr& saveLoadMenu);

    bool isSidePanelOpen(
        const InventoryMgr& inventoryMgr,
        const TakeMgr& takeMgr,
        const InteractionMgr& interactionMgr) const;

    private:
    UiMode mode = UiMode::Gameplay;
};

}

#endif /* UI_COORDINATOR_H */