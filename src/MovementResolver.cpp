#include "MovementResolver.h"

#include <raylib.h>

namespace highline_ridge
{

namespace
{

bool movementBlanketAllows(const MovementStruct& blanket, const std::string& direction)
{
    if (direction == "up")
        return blanket.up;
    if (direction == "down")
        return blanket.down;
    if (direction == "forward")
        return blanket.forward;
    if (direction == "backward")
        return blanket.backward;
    if (direction == "left")
        return blanket.left;
    if (direction == "right")
        return blanket.right;
    return false;
}

bool movementStructHasDirection(const MovementStruct& movement, const std::string& direction)
{
    return movementBlanketAllows(movement, direction);
}

const SubSceneDef* findSubScene(const SceneData& scene, const std::string& subSceneId)
{
    std::map<std::string, SubSceneDef>::const_iterator it = scene.subScenes.find(subSceneId);
    if (it == scene.subScenes.end())
        return nullptr;
    return &it->second;
}

bool sceneStateProvidesLight(
    const SceneData& scene,
    const std::string& activeSubSceneId,
    const MaskEvalContext& context)
{
    const SubSceneDef* subScene = findSubScene(scene, activeSubSceneId);
    if (subScene != nullptr && subScene->providesLight())
        return true;

    if (context.storyFlags == nullptr)
        return false;

    const std::string prefix = scene.id + ":";
    for (const std::string& flag : *context.storyFlags)
    {
        if (flag.find(prefix) == 0 && flag.find("lanterns_lit") != std::string::npos)
            return true;
    }

    return false;
}

bool milestoneHookActive(
    const MovementMappingDef& mapping,
    const MilestoneManager* milestoneMgr,
    bool enabling)
{
    if (milestoneMgr == nullptr)
        return false;

    const std::vector<MilestoneMaskHook>& hooks = enabling
        ? mapping.onMilestoneEnable
        : mapping.onMilestoneDisable;

    for (const MilestoneMaskHook& hook : hooks)
    {
        if (milestoneMgr->getStatus(hook.milestoneId) == hook.when)
            return true;
    }

    return false;
}

}

bool MovementResolver::isDirectionBlanketed(
    const SceneData& scene,
    const std::string& activeSubSceneId,
    const std::string& direction)
{
    const SubSceneDef* subScene = findSubScene(scene, activeSubSceneId);
    if (subScene == nullptr)
        return true;

    if (!movementStructHasDirection(subScene->movement, direction))
        return false;

    return movementBlanketAllows(subScene->movementBlanket, direction);
}

bool MovementResolver::isMappingEffectivelyMasked(
    const MovementMappingDef& mapping,
    const MaskEvalContext& context)
{
    bool masked = mapping.defaultMasked;

    if (isMaskConditionMet(mapping.unmaskWhen, context))
        masked = false;

    if (milestoneHookActive(mapping, context.milestoneMgr, true))
        masked = false;

    if (milestoneHookActive(mapping, context.milestoneMgr, false))
        masked = true;

    return masked;
}

bool MovementResolver::targetRequiresLight(
    const SceneDatabase& database,
    const MovementTarget& target)
{
    if (target.empty())
        return false;

    const SceneData* targetScene = database.getScene(target.sceneId);
    if (targetScene == nullptr)
        return false;

    std::string subSceneId = target.subSceneId;
    if (subSceneId.empty())
        subSceneId = targetScene->defaultSubSceneId;

    const SubSceneDef* subScene = findSubScene(*targetScene, subSceneId);
    if (subScene == nullptr)
        return false;

    return subScene->isDark();
}

bool MovementResolver::hasIllumination(
    const SceneData& scene,
    const std::string& activeSubSceneId,
    const MaskEvalContext& context)
{
    if (sceneStateProvidesLight(scene, activeSubSceneId, context))
        return true;

    return playerHasTopLevelItemFlag(context, "light_source");
}

MovementResolution MovementResolver::resolveDirection(
    const SceneDatabase& database,
    const SceneData& scene,
    const std::string& activeSubSceneId,
    const std::string& direction,
    const MaskEvalContext& context)
{
    MovementResolution resolution;

    std::map<std::string, std::vector<MovementMappingDef>>::const_iterator mappingsIt =
        scene.movementExits.find(direction);
    if (mappingsIt == scene.movementExits.end() || mappingsIt->second.empty())
        return resolution;

    if (!isDirectionBlanketed(scene, activeSubSceneId, direction))
        return resolution;

    const bool illuminated = hasIllumination(scene, activeSubSceneId, context);

    std::vector<const MovementMappingDef*> unmasked;
    for (const MovementMappingDef& mapping : mappingsIt->second)
    {
        if (isMappingEffectivelyMasked(mapping, context))
            continue;

        if (!illuminated && targetRequiresLight(database, mapping.target))
            continue;

        unmasked.push_back(&mapping);
    }

    if (unmasked.empty())
        return resolution;

    if (unmasked.size() > 1)
    {
        TraceLog(
            LOG_WARNING,
            "Movement mask ambiguity in scene '%s' direction '%s': %d unmasked mappings; using '%s'",
            scene.id.c_str(),
            direction.c_str(),
            (int)unmasked.size(),
            unmasked.front()->id.c_str());
    }

    resolution.available = true;
    resolution.target = unmasked.front()->target;
    resolution.mappingId = unmasked.front()->id;
    return resolution;
}

}