#include "Summary.h"

#if MANIA_USE_PLUS
bool32 Summary_State_Wait_Hook(bool32 skippedState) {
    if (TouchInfo->count && !ControllerInfo[CONT_P1].keyStart.down)
        ControllerInfo->keyStart.press = true;

    return false;
}
#endif