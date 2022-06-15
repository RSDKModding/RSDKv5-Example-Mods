#include "HUD.h"
#include "Player.h"

ObjectHUD *HUD;

void HUD_Draw(void)
{
    RSDK_THIS(HUD);
    EntityPlayer *player = RSDK_GET_ENTITY(SceneInfo->currentScreenID, Player);

    Mod.Super(HUD->classID, SUPER_DRAW, NULL);
}
