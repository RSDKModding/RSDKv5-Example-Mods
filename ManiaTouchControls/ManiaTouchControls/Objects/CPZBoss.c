#include "CPZBoss.h"

#include "../Helpers.h"

ObjectCPZBoss *CPZBoss;

bool32 CPZBoss_State_HandleMatch_Player_Hook(bool32 skippedState)
{
    if (CheckTouchRect(ScreenInfo->size.x - 0x80, 0, ScreenInfo->size.x, 0x40, NULL, NULL) >= 0) {
        if (!ControllerInfo[CONT_P1].keyStart.down)
            ControllerInfo[CONT_P1].keyStart.press = true;
    }

    return false;
}