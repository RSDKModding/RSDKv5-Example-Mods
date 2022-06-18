#include "TryAgain.h"

ObjectTryAgain *TryAgain;

bool32 TryAgain_State_Stinger_Hook(bool32 skippedState)
{
    RSDK_THIS(TryAgain);

    if (TouchInfo->count && self->timer < 600)
        self->timer = 600 - 1; // increments by 1 during the state

    return false;
}
