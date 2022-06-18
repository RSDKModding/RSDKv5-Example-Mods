#include "TryAgainE.h"

#if MANIA_USE_PLUS
ObjectTryAgainE *TryAgainE;

bool32 TryAgainE_State_Stinger_Hook(bool32 skippedState)
{
    RSDK_THIS(TryAgainE);

    if (TouchInfo->count && self->timer < 600)
        self->timer = 600 - 1; // increments by 1 during the state

    return false;
}
#endif
