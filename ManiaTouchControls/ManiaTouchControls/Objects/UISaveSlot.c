#include "UISaveSlot.h"

bool32 UISaveSlot_State_Selected_Hook(bool32 skippedState)
{
    ControllerInfo->keyC.down |= TouchInfo->count;
    return false;
}
