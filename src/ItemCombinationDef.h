#ifndef ITEM_COMBINATION_DEF_H
#define ITEM_COMBINATION_DEF_H

#include <string>
#include <vector>

namespace testgame
{

struct ItemCombineRequirements
{
    std::vector<std::string> requiredFlags;
    std::vector<std::string> forbiddenFlags;
};

struct ItemCombineEffect
{
    enum class Type
    {
        Remove,
        AddFlag,
        Grant
    };

    Type type = Type::Grant;
    std::string itemId;
    std::string flag;
};

struct ItemCombineRecipe
{
    std::string id;
    std::string itemA;
    std::string itemB;
    ItemCombineRequirements requirementsA;
    ItemCombineRequirements requirementsB;
    std::vector<ItemCombineEffect> effects;
};

struct ItemCombineApplication
{
    bool success = false;
    std::vector<std::string> removeItemIds;
    std::vector<std::pair<std::string, std::string>> addFlags;
    std::vector<std::string> grantItemIds;
};

}

#endif /* ITEM_COMBINATION_DEF_H */