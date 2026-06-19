#ifndef INVENTORY_ITEM_H
#define INVENTORY_ITEM_H

#include <raylib.h>
#include <string>

namespace testgame
{

struct InventoryItem
{
    std::string id;
    std::string name;
    Texture2D icon{};
    Texture2D examineImage{};
    std::string examineText;
};

}

#endif /* INVENTORY_ITEM_H */