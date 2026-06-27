#ifndef MOVEMENT_RESOLVER_H
#define MOVEMENT_RESOLVER_H

#include <MaskEvaluator.h>
#include <MovementMappingDef.h>
#include <SceneLoader.h>
#include <string>

namespace highline_ridge
{

struct MovementResolution
{
    bool available = false;
    MovementTarget target;
    std::string mappingId;
};

class MovementResolver
{
    public:
    static bool isDirectionBlanketed(
        const SceneData& scene,
        const std::string& activeSubSceneId,
        const std::string& direction);

    static bool isMappingEffectivelyMasked(
        const MovementMappingDef& mapping,
        const MaskEvalContext& context);

    static bool targetRequiresLight(
        const SceneDatabase& database,
        const MovementTarget& target);

    static bool hasIllumination(
        const SceneData& scene,
        const std::string& activeSubSceneId,
        const MaskEvalContext& context);

    static MovementResolution resolveDirection(
        const SceneDatabase& database,
        const SceneData& scene,
        const std::string& activeSubSceneId,
        const std::string& direction,
        const MaskEvalContext& context);
};

}

#endif /* MOVEMENT_RESOLVER_H */