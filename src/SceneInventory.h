#ifndef SCENE_INVENTORY_H
#define SCENE_INVENTORY_H

#include <ItemInstance.h>
#include <MaskEvaluator.h>
#include <SceneInventoryDef.h>
#include <map>
#include <string>
#include <vector>

namespace highline_ridge
{

using SceneInventoryState = std::map<std::string, std::vector<ItemInstance>>;

void ensureSceneInventoryInitialized(
    SceneInventoryState& inventories,
    const std::string& sceneId,
    const std::vector<SceneInventoryEntryDef>& definitions,
    const MaskEvalContext& context);

std::vector<const ItemInstance*> getVisibleSceneInventory(
    const SceneInventoryState& inventories,
    const std::string& sceneId,
    const std::vector<SceneInventoryEntryDef>& definitions,
    const MaskEvalContext& context);

bool sceneInventoryHasItem(
    const SceneInventoryState& inventories,
    const std::string& sceneId,
    const std::string& defId);

bool removeSceneInventoryItem(
    SceneInventoryState& inventories,
    const std::string& sceneId,
    const std::string& instanceId);

}

#endif /* SCENE_INVENTORY_H */