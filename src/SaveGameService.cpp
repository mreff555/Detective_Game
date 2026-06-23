#include "SaveGameService.h"

namespace testgame
{

bool SaveGameService::quickSave(const SavedGameState& state) const
{
    SaveSlotMetadata metadata;
    metadata.name = "Quick Save";
    metadata.timestampIso = currentTimestampIso(metadata.unixTime);
    metadata.isQuickSave = true;
    return writeSaveFile(quickSavePath(), state, metadata);
}

bool SaveGameService::namedSave(
    const SavedGameState& state,
    const std::string& saveName,
    int maxNamedSaves) const
{
    if (saveName.empty())
        return false;

    enforceNamedSaveLimit(maxNamedSaves);

    SaveSlotMetadata metadata;
    metadata.name = saveName;
    metadata.timestampIso = currentTimestampIso(metadata.unixTime);
    metadata.isQuickSave = false;
    return writeSaveFile(buildNamedSavePath(metadata.unixTime), state, metadata);
}

bool SaveGameService::loadFromPath(const std::string& path, SavedGameState& outState) const
{
    return readSaveFile(path, outState);
}

std::vector<SaveSlotListing> SaveGameService::listSlots() const
{
    return listSaveSlots();
}

}