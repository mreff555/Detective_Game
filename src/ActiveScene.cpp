#include "ActiveScene.h"

namespace testgame
{

ActiveScene::ActiveScene()
{
}

void ActiveScene::loadFromStruct(const std::string& id, const LocationStruct& locationStruct)
{
    unloadOwnedImage();
    sceneId = id;
    view = locationStruct;
}

void ActiveScene::unloadOwnedImage()
{
    if (view.ownsLocationImage && view.locationImage.id != 0)
    {
        UnloadTexture(view.locationImage);
        view.locationImage = Texture2D{};
        view.ownsLocationImage = false;
    }
}

}