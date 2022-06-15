#include "HUD.h"
#include "Player.h"

ObjectHUD *HUD;

void HUD_Draw(void)
{
    RSDK_THIS(HUD);
    EntityPlayer *player = RSDK_GET_ENTITY(SceneInfo->currentScreenID, Player);

    Object *debugMode = Mod.FindObject("DebugMode");
    void (*HUD_DrawNumbersBase16)(Vector2 * drawPos, int32 value) = Mod.GetPublicFunction(NULL, "HUD_DrawNumbersBase16");


    if (debugMode && HUD_DrawNumbersBase16) {
        if (player->camera) {
            Vector2 debugPos;

            // Draw this (its drawn when debug mode is on by default
            if (RSDK_GET_ENTITY(SLOT_PLAYER1, Player)->classID != debugMode->classID) {
                // Draw Camera YPos
                debugPos.x = (ScreenInfo[SceneInfo->currentScreenID].width - 16) << 16;
                debugPos.y = 0x180000;
                HUD_DrawNumbersBase16(&debugPos, ScreenInfo[SceneInfo->currentScreenID].position.y);

                // Draw Camera XPos
                debugPos.x -= 0x90000;
                HUD_DrawNumbersBase16(&debugPos, ScreenInfo[SceneInfo->currentScreenID].position.x);

                // Draw Player YPos
                debugPos.x = (ScreenInfo[SceneInfo->currentScreenID].width - 16) << 16;
                debugPos.y += 0x100000;
                HUD_DrawNumbersBase16(&debugPos, (player->position.y >> 0x10));

                // Draw Player XPos
                debugPos.x -= 0x90000;
                HUD_DrawNumbersBase16(&debugPos, (player->position.x >> 0x10));
            }

            // Draw Player YVel
            debugPos.x = (ScreenInfo[SceneInfo->currentScreenID].width - 16) << 16;
            debugPos.y = 0x380000;
            HUD_DrawNumbersBase16(&debugPos, (player->velocity.y >> 0x10));

            // Draw Player XVel
            debugPos.x -= 0x90000;
            HUD_DrawNumbersBase16(&debugPos, player->onGround ? (player->groundVel >> 0x10) : (player->velocity.x >> 0x10));

            // Draw Player collision layers
            debugPos.x = (ScreenInfo[SceneInfo->currentScreenID].width - 16) << 16;
            debugPos.y += 0x100000;
            HUD_DrawNumbersBase16(&debugPos, player->collisionLayers);

            // Draw Player angle
            debugPos.x -= 0x90000;
            HUD_DrawNumbersBase16(&debugPos, player->angle);

            // Draw Player collision plane
            debugPos.x = (ScreenInfo[SceneInfo->currentScreenID].width - 16) << 16;
            debugPos.y += 0x100000;
            HUD_DrawNumbersBase16(&debugPos, player->collisionPlane);

            // Draw Player collision mode
            debugPos.x -= 0x90000;
            HUD_DrawNumbersBase16(&debugPos, player->collisionMode);
        }
    }

    Mod.Super(HUD->classID, SUPER_DRAW, NULL);
}
