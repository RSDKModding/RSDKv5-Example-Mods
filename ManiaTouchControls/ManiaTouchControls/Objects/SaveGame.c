#include "SaveGame.h"

// Ported from Mania's SaveGame_GetDataPtr
SaveRAM *SaveGame_GetSaveRAM()
{
    if (globals->saveSlotID == NO_SAVE_SLOT)
        return (SaveRAM *)globals->noSaveSlot;

#if MANIA_USE_PLUS
    if (globals->gameMode == MODE_ENCORE)
        return (SaveRAM *)&globals->saveRAM[0x100 * (globals->saveSlotID % 3 + 10)];
    else
#endif
        return (SaveRAM *)&globals->saveRAM[0x100 * (globals->saveSlotID % 8)];
}