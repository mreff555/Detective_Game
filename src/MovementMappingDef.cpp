#include "MovementMappingDef.h"

namespace highline_ridge
{

MovementTarget parseMovementTarget(const std::string& rawTarget)
{
    MovementTarget target;
    if (rawTarget.empty())
        return target;

    const size_t hashPos = rawTarget.find('#');
    if (hashPos == std::string::npos)
    {
        target.sceneId = rawTarget;
        return target;
    }

    target.sceneId = rawTarget.substr(0, hashPos);
    target.subSceneId = rawTarget.substr(hashPos + 1);
    return target;
}

}