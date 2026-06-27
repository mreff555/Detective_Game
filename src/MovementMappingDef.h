#ifndef MOVEMENT_MAPPING_DEF_H
#define MOVEMENT_MAPPING_DEF_H

#include <MaskConditionDef.h>
#include <string>
#include <vector>

namespace highline_ridge
{

struct MovementTarget
{
    std::string sceneId;
    std::string subSceneId;

    bool empty() const { return sceneId.empty(); }
};

struct MovementMappingDef
{
    std::string id;
    MovementTarget target;
    bool defaultMasked = false;
    std::string exclusiveGroup;
    MaskCondition unmaskWhen;
    std::vector<MilestoneMaskHook> onMilestoneEnable;
    std::vector<MilestoneMaskHook> onMilestoneDisable;
};

MovementTarget parseMovementTarget(const std::string& rawTarget);

}

#endif /* MOVEMENT_MAPPING_DEF_H */