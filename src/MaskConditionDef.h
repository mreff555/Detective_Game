#ifndef MASK_CONDITION_DEF_H
#define MASK_CONDITION_DEF_H

#include <MilestoneStruct.h>
#include <string>
#include <vector>

namespace highline_ridge
{

enum class MaskConditionType
{
    None,
    All,
    Any,
    Flag,
    MilestoneStarted,
    MilestoneComplete,
    MilestoneFailed,
    PlayerHasItem,
    PlayerHasItemFlag,
    SubSceneActive
};

struct MaskCondition
{
    MaskConditionType type = MaskConditionType::None;
    std::string value;
    std::vector<MaskCondition> children;
};

struct MilestoneMaskHook
{
    std::string milestoneId;
    MilestoneStatus when = MilestoneStatus::Complete;
};

}

#endif /* MASK_CONDITION_DEF_H */