#include "GameAPI/Game.h"

#if MANIA_USE_PLUS
StateMachine(OOZ2Outro_State_BoardSub) = NULL;
StateMachine(OOZ2Outro_State_SubActivate) = NULL;

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
