ObjectHeavyShinobi *HeavyShinobi;

StateMachine(HeavyShinobi_State_Setup);

bool32 HeavyShinobi_State_Setup_Hook(bool32 skip)
{
    RSDK_THIS(HeavyShinobi);

    Zone->cameraBoundsR[0] -= extraWidth;
    return true;
}
