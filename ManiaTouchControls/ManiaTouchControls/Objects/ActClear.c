#include "ActClear.h"

#include "../Helpers.h"

bool32 ActClear_State_TallyScore_Hook(bool32 skippedState)
{
    if (TouchInfo->count && !ControllerInfo[CONT_P1].keyStart.down)
        ControllerInfo[CONT_P1].keyStart.press = true;

    return false;
}
#if MANIA_USE_PLUS
bool32 ActClear_State_ShowResultsTA_Hook(bool32 skippedState)
{
    if (API.CheckDLC(DLC_PLUS) && CheckTouchPause()) {
        if (!ControllerInfo[CONT_P1].keyY.down)
            ControllerInfo->keyY.press = true;
    }

    ControllerInfo->keyStart.press |= TouchInfo->count && !ControllerInfo->keyY.press;

    return false;
}
#endif