#ifndef PLAYER_STATS_H
#define PLAYER_STATS_H

#include <ConversationStruct.h>
#include <set>
#include <string>

namespace testgame
{

struct PlayerStatPercents
{
    float health = 90.0f;
    float energy = 20.0f;
    float resolve = 50.0f;
    float lucidity = 30.0f;
    float charisma = 50.0f;
};

class PlayerStats
{
    public:
    float health = 90.0f;
    float energy = 20.0f;
    float resolve = 50.0f;
    float lucidity = 30.0f;
    float charisma = 50.0f;
    float walletCash = 20.0f;
    std::set<std::string> consumedStatusActions;

    bool apply(const StatusEffect& effect, bool allowRepeat);
    PlayerStatPercents toPercents() const;
};

}

#endif /* PLAYER_STATS_H */