#ifndef SCENE_CONTROLLER_H
#define SCENE_CONTROLLER_H

#include <ActiveScene.h>
#include <AudioManager.h>
#include <MaskEvaluator.h>
#include <MovementResolver.h>
#include <SceneLoader.h>
#include <functional>
#include <string>

namespace highline_ridge
{

class InventoryMgr;
class InteractionMgr;
class ItemDatabase;
class MilestoneManager;
class TakeMgr;
class WorldState;

class SceneController
{
    public:
    SceneController(
        SceneDatabase& sceneDatabase,
        AudioManager& audioManager);

    const ActiveScene& getActiveScene() const { return activeScene; }
    ActiveScene& getActiveScene() { return activeScene; }
    const std::string& getCurrentSceneId() const { return activeScene.getId(); }

    bool loadInitialScene(const std::string& sceneId, WorldState& worldState);
    bool transitionToScene(
        const std::string& nextSceneId,
        const std::string& nextSubSceneId,
        WorldState& worldState,
        TakeMgr& takeMgr,
        InteractionMgr& interactionMgr,
        InventoryMgr& inventoryMgr,
        const ItemDatabase& itemDatabase,
        const MilestoneManager& milestoneMgr,
        const std::function<bool(const std::string& phaseId)>& isPhaseComplete = nullptr);
    bool tryMove(
        const std::string& direction,
        WorldState& worldState,
        TakeMgr& takeMgr,
        InteractionMgr& interactionMgr,
        InventoryMgr& inventoryMgr,
        const ItemDatabase& itemDatabase,
        const MilestoneManager& milestoneMgr,
        const std::function<bool(const std::string& phaseId)>& isPhaseComplete = nullptr);
    bool isDirectionAvailable(
        const std::string& direction,
        const WorldState& worldState,
        const InventoryMgr& inventoryMgr,
        const ItemDatabase& itemDatabase,
        const MilestoneManager& milestoneMgr) const;

    MaskEvalContext buildMaskContext(
        const WorldState& worldState,
        const InventoryMgr& inventoryMgr,
        const ItemDatabase& itemDatabase,
        const MilestoneManager& milestoneMgr) const;

    private:
    bool applySceneStruct(
        const LocationStruct& locationStruct,
        const std::string& fromRoom,
        WorldState& worldState);

    SceneDatabase& sceneDatabase;
    AudioManager& audioManager;
    ActiveScene activeScene;
};

}

#endif /* SCENE_CONTROLLER_H */