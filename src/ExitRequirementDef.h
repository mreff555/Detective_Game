#ifndef EXIT_REQUIREMENT_DEF_H
#define EXIT_REQUIREMENT_DEF_H

#include <string>
#include <vector>

namespace highline_ridge
{

struct ExitRequirementDef
{
    bool requiresLightSource = false;
    bool requiresRoomPurchasedToday = false;
    std::string requiresInventoryItem;
    std::vector<std::string> requiresInventoryItems;
    std::string requiresStoryFlag;
    std::string blockedDetails;
};

}

#endif /* EXIT_REQUIREMENT_DEF_H */