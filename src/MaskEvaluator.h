#ifndef MASK_EVALUATOR_H
#define MASK_EVALUATOR_H

#include <MaskConditionDef.h>
#include <MilestoneManager.h>
#include <functional>
#include <set>
#include <string>

namespace highline_ridge
{

class InventoryMgr;
class ItemDatabase;

struct MaskEvalContext
{
    const std::set<std::string>* storyFlags = nullptr;
    const MilestoneManager* milestoneMgr = nullptr;
    const InventoryMgr* inventoryMgr = nullptr;
    const ItemDatabase* itemDatabase = nullptr;
    std::string activeSubSceneId;
    std::function<bool(const std::string& itemDefId)> sceneInventoryHasItem;
    std::function<bool(const std::string& itemFlag)> sceneInventoryHasItemFlag;
};

bool evaluateMaskCondition(const MaskCondition& condition, const MaskEvalContext& context);
bool isMaskConditionMet(const MaskCondition& condition, const MaskEvalContext& context);
bool playerHasTopLevelItemFlag(
    const MaskEvalContext& context,
    const std::string& flag);

}

#endif /* MASK_EVALUATOR_H */