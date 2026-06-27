#ifndef SCENE_INVENTORY_DEF_H
#define SCENE_INVENTORY_DEF_H

#include <ItemInstance.h>
#include <MaskConditionDef.h>
#include <string>

namespace highline_ridge
{

struct SceneInventoryEntryDef
{
    ItemInstance instance;
    MaskCondition unmaskWhen;
    bool infiniteQuantity = false;
};

}

#endif /* SCENE_INVENTORY_DEF_H */