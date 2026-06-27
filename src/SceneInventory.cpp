#include "SceneInventory.h"

namespace highline_ridge
{

namespace
{

bool inventoryContainsInstance(
    const std::vector<ItemInstance>& inventory,
    const std::string& instanceId)
{
    for (const ItemInstance& item : inventory)
    {
        if (item.instanceId == instanceId)
            return true;
    }
    return false;
}

bool definitionIsVisible(
    const SceneInventoryEntryDef& definition,
    const MaskEvalContext& context)
{
    return isMaskConditionMet(definition.unmaskWhen, context);
}

}

void ensureSceneInventoryInitialized(
    SceneInventoryState& inventories,
    const std::string& sceneId,
    const std::vector<SceneInventoryEntryDef>& definitions,
    const MaskEvalContext& context)
{
    (void)context;

    std::vector<ItemInstance>& inventory = inventories[sceneId];
    for (const SceneInventoryEntryDef& definition : definitions)
    {
        if (inventoryContainsInstance(inventory, definition.instance.instanceId))
            continue;

        inventory.push_back(definition.instance);
    }
}

std::vector<const ItemInstance*> getVisibleSceneInventory(
    const SceneInventoryState& inventories,
    const std::string& sceneId,
    const std::vector<SceneInventoryEntryDef>& definitions,
    const MaskEvalContext& context)
{
    std::vector<const ItemInstance*> visible;
    SceneInventoryState::const_iterator inventoryIt = inventories.find(sceneId);
    if (inventoryIt == inventories.end())
        return visible;

    for (const ItemInstance& item : inventoryIt->second)
    {
        for (const SceneInventoryEntryDef& definition : definitions)
        {
            if (definition.instance.instanceId != item.instanceId)
                continue;

            if (!definitionIsVisible(definition, context))
                break;

            visible.push_back(&item);
            break;
        }
    }

    return visible;
}

bool sceneInventoryHasItem(
    const SceneInventoryState& inventories,
    const std::string& sceneId,
    const std::string& defId)
{
    SceneInventoryState::const_iterator inventoryIt = inventories.find(sceneId);
    if (inventoryIt == inventories.end())
        return false;

    for (const ItemInstance& item : inventoryIt->second)
    {
        if (item.defId == defId)
            return true;
    }

    return false;
}

bool removeSceneInventoryItem(
    SceneInventoryState& inventories,
    const std::string& sceneId,
    const std::string& instanceId)
{
    SceneInventoryState::iterator inventoryIt = inventories.find(sceneId);
    if (inventoryIt == inventories.end())
        return false;

    std::vector<ItemInstance>& inventory = inventoryIt->second;
    for (std::vector<ItemInstance>::iterator it = inventory.begin(); it != inventory.end(); ++it)
    {
        if (it->instanceId != instanceId)
            continue;

        inventory.erase(it);
        return true;
    }

    return false;
}

}