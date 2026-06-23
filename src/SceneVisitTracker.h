#ifndef SCENE_VISIT_TRACKER_H
#define SCENE_VISIT_TRACKER_H

#include <set>
#include <string>

namespace testgame
{

struct SceneVisitTracker
{
    bool hasSpokenInCurrentScene = false;
    bool hasUsedInCurrentScene = false;
    std::set<std::string> examinedSceneIds;
    std::set<std::string> usedSceneIds;

    void resetForNewScene();
    bool hasExaminedScene(const std::string& sceneId) const;
};

}

#endif /* SCENE_VISIT_TRACKER_H */