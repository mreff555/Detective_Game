#ifndef PROGRESSION_SERVICE_H
#define PROGRESSION_SERVICE_H

#include <MilestoneManager.h>
#include <SaveGame.h>
#include <set>
#include <string>

namespace highline_ridge
{

class ConversationManager;

class ProgressionService
{
    public:
    ProgressionService(MilestoneManager& milestoneMgr);

    void evaluate(
        const std::set<std::string>& storyFlags,
        const ConversationManager& conversationMgr,
        const std::string& sceneId,
        const std::function<bool(const std::string& itemId)>& hasItem);

    void syncFromLegacyState(
        const std::set<std::string>& storyFlags,
        const ConversationPersistState& conversation,
        const std::function<bool(const std::string& itemId)>& hasItem);

    bool hasStoryFlag(const std::set<std::string>& storyFlags, const std::string& flag) const;
    MilestoneStatus getMilestoneStatus(const std::string& milestoneId) const;
    std::vector<const MilestoneDef*> getVisibleQuests() const;

    private:
    MilestoneManager& milestoneMgr;
};

}

#endif /* PROGRESSION_SERVICE_H */