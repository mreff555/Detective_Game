#ifndef EXIT_REQUIREMENT_DEF_H
#define EXIT_REQUIREMENT_DEF_H

#include <string>

namespace testgame
{

struct ExitRequirementDef
{
    bool requiresLightSource = false;
    std::string blockedDetails;
};

}

#endif /* EXIT_REQUIREMENT_DEF_H */