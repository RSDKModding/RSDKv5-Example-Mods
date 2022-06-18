#include "HUD.h"
#include "Player.h"

ObjectHUD *HUD;

void HUD_Draw(void)
{
    RSDK_THIS(HUD);

    int32 lifeOffsetX  = self->lifeOffset.x;
    self->lifeOffset.x = 0x7FFF0000;

    Mod.Super(HUD->classID, SUPER_DRAW, NULL);

    self->lifeOffset.x = lifeOffsetX;
}
