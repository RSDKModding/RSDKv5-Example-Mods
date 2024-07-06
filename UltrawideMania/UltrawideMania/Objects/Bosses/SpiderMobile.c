#include "../All.h"
ObjectSpiderMobile *SpiderMobile;

StateMachine(SpiderMobile_StateBody_AwaitPlayer);

bool32 SpiderMobile_StateBody_AwaitPlayer_Hook(bool32 skip)
{
    RSDK_THIS(SpiderMobile);

    if (self->state == SpiderMobile_StateBody_AwaitPlayer)
        return false;

    Zone->cameraBoundsL[0] = (self->position.x >> 16) - ScreenInfo->center.x;
    Zone->cameraBoundsR[0] = (self->position.x >> 16) + ScreenInfo->center.x;

    SpiderMobile->boundsL = (Zone->cameraBoundsL[0] + 64) << 16;
    SpiderMobile->boundsR = (Zone->cameraBoundsR[0] - 64) << 16;

    return true;
}
