#include "BSS_HUD.h"
#include "BSS_Setup.h"

ObjectBSS_HUD *BSS_HUD;

void BSS_HUD_StaticUpdate(void)
{
    if (ControllerInfo->keySelect.press)
        BSS_HUD->debugEnabled ^= 1;
}

void BSS_HUD_Draw(void)
{
    RSDK_THIS(BSS_HUD);

    Mod.Super(BSS_HUD->classID, SUPER_DRAW, NULL);

    ObjectBSS_Setup *bssSetup = Mod.FindObject("BSS_Setup");

    if (BSS_HUD->debugEnabled) {
        uint16 *playFields[3] = { bssSetup->playField, bssSetup->sphereChainTable, bssSetup->sphereCollectedTable };

        uint32 colors[24] = {
            0x000000, 0x0000FF, 0xFF0000, 0xFFFFFF, 0xFFFF00, 0x00FF00, 0xFF00FF, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000,
            0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000
        };

        for (int32 p = 0; p < 3; ++p) {
            for (int32 y = 0; y < BSS_PLAYFIELD_H; ++y) {
                for (int32 x = 0; x < BSS_PLAYFIELD_W; ++x) {
                    int32 playFieldPos = (x * BSS_PLAYFIELD_H) + y;
                    uint16 type        = playFields[p][playFieldPos] & 0x7F;

                    RSDK.DrawRect((ScreenInfo->size.x - 64) + (x << 1), (ScreenInfo->size.y - (3 * 64)) + (p * 64) + (y << 1), 2, 2, colors[type],
                                  0xFF, INK_NONE, true);
                }
            }
        }
    }
}
