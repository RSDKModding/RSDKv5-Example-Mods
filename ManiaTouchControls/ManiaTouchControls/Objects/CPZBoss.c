#include "CPZBoss.h"

#include "../Helpers.h"

ObjectCPZBoss *CPZBoss;

bool32 CPZBoss_State_HandleMatch_Player_Hook(bool32 skippedState)
{
    if (CheckTouchPause()) {
        if (!ControllerInfo[CONT_P1].keyStart.down)
            ControllerInfo[CONT_P1].keyStart.press = true;
    }

    return false;
}