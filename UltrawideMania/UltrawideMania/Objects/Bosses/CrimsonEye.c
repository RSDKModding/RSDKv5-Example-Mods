#include "../../ModConfig.h"

StateMachine(CrimsonEye_StateContainer_SetupArena);
StateMachine(CrimsonEye_StateContainer_AwaitPlayer);
ObjectCrimsonEye *CrimsonEye;

bool32 CrimsonEye_StateContainer_SetupArena_Hook(bool32 skip)
{
    RSDK_THIS(CrimsonEye);

    if (self->state == CrimsonEye_StateContainer_AwaitPlayer)
        Zone->cameraBoundsR[0] = (self->position.x >> 16) + WIDE_SCR_XCENTER + 80;

    return false;
}

bool32 CrimsonEye_StateContainer_AwaitPlayer_Hook(bool32 skip)
{
    RSDK_THIS(CrimsonEye);

    EntityPlayer *player1 = RSDK_GET_ENTITY(SLOT_PLAYER1, Player);
    if (player1->position.x > self->position.x - 0x500000)
        Zone->cameraBoundsL[0] = (self->position.x >> 16) - WIDE_SCR_XCENTER - 80;

    return false;
}