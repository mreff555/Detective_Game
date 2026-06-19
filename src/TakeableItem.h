#ifndef TAKEABLE_ITEM_H
#define TAKEABLE_ITEM_H

#include <raylib.h>
#include <string>

namespace testgame
{

struct TakeableItem
{
    std::string id;
    std::string name;
    std::string iconPath;
    std::string examineImagePath;
    std::string examineText;
    std::string takeMessage;
    Texture2D icon{};
};

}

#endif /* TAKEABLE_ITEM_H */