StateMachine(SpiderMobile_StateBody_AwaitPlayer);
ObjectSpiderMobile *SpiderMobile;

int32 preTimer;

bool32 SpiderMobile_StateBody_AwaitPlayer_Pre(bool32 skip) {
    RSDK_THIS(SpiderMobile);
    preTimer = self->timer;

    return false;
}

bool32 SpiderMobile_StateBody_AwaitPlayer_Hook(bool32 skip)
{
    RSDK_THIS(SpiderMobile);

    if (self->timer || !preTimer)
        return false;

    Zone->cameraBoundsL[0] = (self->position.x >> 16) - ScreenInfo->centerX;
    Zone->cameraBoundsR[0] = (self->position.x >> 16) + ScreenInfo->centerX;

    SpiderMobile->boundsL = (Zone->cameraBoundsL[0] + 64) << 16;
    SpiderMobile->boundsR = (Zone->cameraBoundsR[0] - 64) << 16;

    return true;
}