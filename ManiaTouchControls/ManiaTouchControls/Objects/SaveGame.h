#ifndef OBJ_SAVEGAME_H
#define OBJ_SAVEGAME_H

#include "GameAPI/Game.h"

typedef enum {
    SAVEGAME_BLANK,
    SAVEGAME_INPROGRESS,
    SAVEGAME_COMPLETE,
} SaveGameStates;

typedef enum {
    SAVERECALL_NORMAL,
    SAVERECALL_DISABLED,
    SAVERECALL_BROKENITEMBOX,
} SaveRecallStates;

// Using a seperate SaveRAM struct
// Normally (and officially) the EntitySaveGame struct was used here
// but due to v5U updating the entity (and thus the SaveGame "spec")
// EntitySaveGame is no longer easily compatible across versions
// so I gave it dummy data and will be using this struct to interact with saveRAM
typedef struct {
    uint8 padding[0x58];

    int32 saveState;
    int32 characterID;
    int32 zoneID;
    int32 lives;
    int32 score;
    int32 score1UP;
    int32 chaosEmeralds;
    int32 continues;
    int32 storedStageID;
    int32 nextSpecialStage;
    int32 collectedSpecialRings;
    int32 medalMods;
#if MANIA_USE_PLUS
    //(AIZ if encore) + GHZ-TMZ + (ERZ if not encore)
    // Bonus stage is [28]
    // Special stage is [29]
    // the rest are unused
    int32 zoneTimes[32];
    int32 characterFlags;
    int32 stock;
    int32 playerID; // encore playerID
#endif
} SaveRAM;

#if MANIA_USE_PLUS
extern int32 (*SaveGame_GetDataPtr)(int32 slot, bool32 encore);
#else
extern int32 (*SaveGame_GetDataPtr)(int32 slot);
#endif

SaveRAM *SaveGame_GetSaveRAM();


#endif //! OBJ_SAVEGAME_H
