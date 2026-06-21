#ifndef ITEM_COMBINATION_DATABASE_H
#define ITEM_COMBINATION_DATABASE_H

#include <ItemCombinationDef.h>
#include <ItemInstance.h>
#include <string>
#include <vector>

namespace testgame
{

class ItemCombinationDatabase
{
    public:
    bool load(const std::string& path);

    bool tryCombine(
        const std::string& firstItemId,
        const std::string& secondItemId,
        const ItemInstance& firstInstance,
        const ItemInstance& secondInstance,
        ItemCombineApplication& outApplication) const;

    private:
    bool requirementsMet(
        const ItemCombineRequirements& requirements,
        const ItemInstance& instance) const;

    bool recipeMatches(
        const ItemCombineRecipe& recipe,
        const std::string& firstItemId,
        const std::string& secondItemId,
        const ItemInstance& firstInstance,
        const ItemInstance& secondInstance) const;

    std::vector<ItemCombineRecipe> recipes;
};

}

#endif /* ITEM_COMBINATION_DATABASE_H */