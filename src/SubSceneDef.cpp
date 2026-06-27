#include "SubSceneDef.h"

#include <algorithm>

namespace highline_ridge
{

bool SubSceneDef::hasFlag(const std::string& flag) const
{
    return std::find(flags.begin(), flags.end(), flag) != flags.end();
}

}