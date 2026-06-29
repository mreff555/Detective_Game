#ifndef LOCATION_STRUCT_H
#define LOCATION_STRUCT_H

#include <ActionStruct.h>
#include <ItemDef.h>
#include <MovementStruct.h>
#include <raylib.h>
#include <string>

namespace highline_ridge
{

struct LocationStruct
{
    Texture2D locationImage;
    bool ownsLocationImage = true;
    bool isUnderConstruction = false;
    std::string locationDescription;
    ItemTtsDef descriptionTts;
    std::string examineDetails;
    ItemTtsDef examineTts;
    std::string examineFlag;
    float examineLucidityDelta = 0.0f;
    bool examineLucidityOncePerDay = false;
    std::string speakDetails;
    std::string useDetails;
    float useHealthDelta = 0.0f;
    float useEnergyDelta = 0.0f;
    bool useRepeatStatus = false;
    bool useRequiresExamine = true;
    bool useAdvancesDay = false;
    std::string useExit;
    Font descriptionFont;
    Font boldFont;
    Font uiFont;
    MovementStruct movementFilter;
    ActionStruct actionFilter;
};

}

#endif /* LOCATION_STRUCT_H */