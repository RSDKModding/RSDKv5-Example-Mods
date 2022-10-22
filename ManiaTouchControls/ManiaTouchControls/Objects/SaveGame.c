#include "SaveGame.h"

#if MANIA_USE_PLUS
int32 (*SaveGame_GetDataPtr)(int32 slot, bool32 encore) = NULL;
#else
int32 (*SaveGame_GetDataPtr)(int32 slot) = NULL;
#endif

SaveRAM *SaveGame_GetSaveRAM()
{
    if (!SaveGame_GetDataPtr)
        return NULL;

#if MANIA_USE_PLUS
    return (SaveRAM *)SaveGame_GetDataPtr(globals->saveSlotID, globals->gameMode == MODE_ENCORE);
#else
    return (SaveRAM *)SaveGame_GetDataPtr(globals->saveSlotID);
#endif
}