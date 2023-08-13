#include "GameAPI/Game.h"

#if MANIA_USE_PLUS
StateMachine(OOZ2Outro_State_BoardSub) = NULL;
StateMachine(OOZ2Outro_State_SubActivate) = NULL;

void OOZ2Outro_State_BoardSub_Hook(void)
{
    ControllerInfo->keyStart.press |= TouchInfo->count;
    return false;
}

void OOZ2Outro_State_SubActivate_Hook(void)
{
    ControllerInfo->keyStart.press |= TouchInfo->count;
    return false;
}
#endif
