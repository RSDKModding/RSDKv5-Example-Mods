#include "../All.h"
ObjectBigSqueeze *BigSqueeze;

StateMachine(BigSqueeze_StateManager_SetupIntro);
StateMachine(BigSqueeze_StateManager_SetupArena);

bool32 BigSqueeze_StateManager_SetupIntro_Hook(bool32 skip)
{
    RSDK_THIS(BigSqueeze);

    if (self->state == BigSqueeze_StateManager_SetupIntro)
        return false;

    Zone->cameraBoundsL[0] = (self->position.x >> 16) - ScreenInfo->center.x;
    return true;
}

bool32 BigSqueeze_StateManager_SetupArena_Hook(bool32 skip)
{
    RSDK_THIS(BigSqueeze);

    if (self->state == BigSqueeze_StateManager_SetupArena)
        return false;

    Zone->cameraBoundsR[0] = (self->position.x >> 16) + ScreenInfo->center.x;
    return true;
}
