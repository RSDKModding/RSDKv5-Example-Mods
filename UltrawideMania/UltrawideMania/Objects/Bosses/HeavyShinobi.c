#include "../All.h"
ObjectHeavyShinobi *HeavyShinobi;

StateMachine(HeavyShinobi_State_Init);

bool32 HeavyShinobi_State_Init_Hook(bool32 skip)
{
    RSDK_THIS(HeavyShinobi);

    if (self->state == HeavyShinobi_State_Init)
        return false;

    Zone->cameraBoundsR[0] = WIDE_SCR_XCENTER + 80 + (self->position.x >> 16);
    return true;
}
