#include "OOZ2Outro.h"

#if MANIA_USE_PLUS
bool32 OOZ2Outro_State_BoardSub_Hook(bool32 skipped)
{
    ControllerInfo->keyStart.press |= TouchInfo->count;
    return false;
}

bool32 OOZ2Outro_State_SubActivate_Hook(bool32 skipped)
{
    ControllerInfo->keyStart.press |= TouchInfo->count;
    return false;
}
#endif
