#include "SceneVisitTracker.h"

namespace highline_ridge
{

void SceneVisitTracker::resetForNewScene()
{
    hasSpokenInCurrentScene = false;
    hasUsedInCurrentScene = false;
}

bool SceneVisitTracker::hasExaminedScene(const std::string& sceneId) const
{
    return examinedSceneIds.count(sceneId) > 0;
}

}