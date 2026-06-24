#ifndef SPEAK_TARGET_DEF_H
#define SPEAK_TARGET_DEF_H

#include <string>

namespace highline_ridge
{

struct SpeakTargetDef
{
    std::string id;
    std::string label;
    std::string phaseId;
    std::string randomLineId;
    bool isWorkTheRoom = false;
};

}

#endif /* SPEAK_TARGET_DEF_H */