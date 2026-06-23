#ifndef GAME_CONTEXT_H
#define GAME_CONTEXT_H

#include <ConversationManager.h>
#include <MilestoneManager.h>
#include <MilestoneStruct.h>
#include <SaveGame.h>
#include <functional>
#include <set>
#include <string>

namespace testgame
{

class GameContext
{
    public:
    static MilestoneEventContext makeMilestoneContext(
        ConversationPersistState& conversationSnapshot,
        const std::set<std::string>& storyFlags,
        const ConversationManager& conversationMgr,
        const std::string& sceneId,
        const MilestoneManager& milestoneMgr,
        const std::function<bool(const std::string& itemId)>& hasItem);
};

}

#endif /* GAME_CONTEXT_H */