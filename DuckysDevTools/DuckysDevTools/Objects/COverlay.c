#include "COverlay.h"
#include "Player.h"
#include "Zone.h"

ObjectCOverlay *COverlay;

void COverlay_Draw(void)
{
    EntityPlayer *player = RSDK_GET_ENTITY(SceneInfo->currentScreenID, Player);
    ObjectZone *Zone     = Mod.FindObject("Zone");

    if (Zone && player) {
        int32 collisionLayers = Zone->collisionLayers;

        Zone->collisionLayers = player->collisionLayers;
        Mod.Super(COverlay->classID, SUPER_DRAW, NULL);
        Zone->collisionLayers = collisionLayers;
    }
    else {
        Mod.Super(COverlay->classID, SUPER_DRAW, NULL);
    }
}
