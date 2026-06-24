#include "GameContext.h"

namespace highline_ridge
{

MilestoneEventContext GameContext::makeMilestoneContext(
    ConversationPersistState& conversationSnapshot,
    const std::set<std::string>& storyFlags,
    const ConversationManager& conversationMgr,
    const std::string& sceneId,
    const MilestoneManager& milestoneMgr,
    const std::function<bool(const std::string& itemId)>& hasItem)
{
    conversationMgr.exportPersistState(conversationSnapshot);

    MilestoneEventContext context;
    context.storyFlags = storyFlags;
    context.conversation = &conversationSnapshot;
    context.sceneId = sceneId;
    context.hasItem = hasItem;
    context.getMilestoneStatus = [&milestoneMgr](const std::string& milestoneId)
    {
        return milestoneMgr.getStatus(milestoneId);
    };
    return context;
}

}