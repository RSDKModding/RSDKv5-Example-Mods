#include "SpecialClear.h"
#include "../Helpers.h"

bool32 SpecialClear_State_TallyScore_Hook(bool32 skippedState)
{
    if (TouchInfo->count && !ControllerInfo->keyStart.down)
        ControllerInfo->keyStart.press = true;

    return false;
}