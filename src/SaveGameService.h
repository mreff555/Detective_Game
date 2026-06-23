#ifndef SAVE_GAME_SERVICE_H
#define SAVE_GAME_SERVICE_H

#include <SaveGame.h>
#include <string>

namespace testgame
{

class SaveGameService
{
    public:
    bool quickSave(const SavedGameState& state) const;
    bool namedSave(const SavedGameState& state, const std::string& saveName, int maxNamedSaves) const;
    bool loadFromPath(const std::string& path, SavedGameState& outState) const;
    std::vector<SaveSlotListing> listSlots() const;
};

}

#endif /* SAVE_GAME_SERVICE_H */