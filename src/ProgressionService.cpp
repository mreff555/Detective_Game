#include "ProgressionService.h"

#include <GameContext.h>

namespace highline_ridge
{

ProgressionService::ProgressionService(MilestoneManager& milestoneMgr_)
    : milestoneMgr(milestoneMgr_)
{
}

void ProgressionService::evaluate(
    const std::set<std::string>& storyFlags,
    const ConversationManager& conversationMgr,
    const std::string& sceneId,
    const std::function<bool(const std::string& itemId)>& hasItem)
{
    ConversationPersistState conversationSnapshot;
    const MilestoneEventContext context = GameContext::makeMilestoneContext(
        conversationSnapshot,
        storyFlags,
        conversationMgr,
        sceneId,
        milestoneMgr,
        hasItem);
    milestoneMgr.evaluate(context);
}

void ProgressionService::syncFromLegacyState(
    const std::set<std::string>& storyFlags,
    const ConversationPersistState& conversation,
    const std::function<bool(const std::string& itemId)>& hasItem)
{
    milestoneMgr.syncFromLegacyState(storyFlags, conversation, hasItem);
}

bool ProgressionService::hasStoryFlag(
    const std::set<std::string>& storyFlags,
    const std::string& flag) const
{
    return storyFlags.count(flag) > 0;
}

MilestoneStatus ProgressionService::getMilestoneStatus(const std::string& milestoneId) const
{
    return milestoneMgr.getStatus(milestoneId);
}

std::vector<const MilestoneDef*> ProgressionService::getVisibleQuests() const
{
    return milestoneMgr.getVisibleQuests();
}

}