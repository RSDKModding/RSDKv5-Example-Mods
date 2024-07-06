#include "../All.h"
ObjectHeavyShinobi *HeavyShinobi;

StateMachine(HeavyShinobi_State_Init);

bool32 HeavyShinobi_State_Init_Hook(bool32 skip)
{
    RSDK_THIS(HeavyShinobi);

    Zone->cameraBoundsR[0] -= extraWidth;
    return true;
}
