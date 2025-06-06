#include "PuyoGame.h"
#include "../Helpers.h"

ObjectPuyoGame *PuyoGame;

void PuyoGame_Update(void)
{
    RSDK_THIS(PuyoGame);

    if (CheckTouchPause()) {
        if (!ControllerInfo->keyStart.down)
            ControllerInfo->keyStart.press = true;
    }

    Mod.Super(PuyoGame->classID, SUPER_UPDATE, NULL);
}

bool32 PuyoGame_State_ShowRoundResults_Hook(bool32 skippedState)
{
    if (TouchInfo->count)
        ControllerInfo[CONT_P1].keyA.down = true;

    return false;
}

bool32 PuyoGame_State_ShowMatchResults_Hook(bool32 skippedState)
{
    if (TouchInfo->count)
        ControllerInfo[CONT_P1].keyA.down = true;

    return false;
}
