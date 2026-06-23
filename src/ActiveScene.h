#ifndef ACTIVE_SCENE_H
#define ACTIVE_SCENE_H

#include <LocationStruct.h>
#include <string>

namespace testgame
{

class ActiveScene
{
    public:
    ActiveScene();

    const std::string& getId() const { return sceneId; }
    const LocationStruct& getView() const { return view; }
    bool isUnderConstruction() const { return view.isUnderConstruction; }

    void loadFromStruct(const std::string& id, const LocationStruct& locationStruct);
    void unloadOwnedImage();

    private:
    std::string sceneId;
    LocationStruct view;
};

}

#endif /* ACTIVE_SCENE_H */