#include "Player.h"

#include "../ModConfig.h"
#include "../Helpers.h"

ObjectPlayer *Player;
ModObjectPlayer *Mod_Player;

bool32 Player_Input_P1_Hook(bool32 skippedState)
{
    RSDK_THIS(Player);

    if (self->controllerID < PLAYER_COUNT) {
        RSDKControllerState *controller = &ControllerInfo[self->controllerID];

        int32 tx = 0, ty = 0;
        if (CheckTouchRect(0, 96, ScreenInfo->center.x, ScreenInfo->size.y, &tx, &ty) >= 0) {
            tx -= config.moveDPadPos.x;
            ty -= config.moveDPadPos.y;

            switch (((RSDK.ATan2(tx, ty) + 32) & 0xFF) >> 6) {
                case 0:
                    ControllerInfo->keyRight.down |= true;
                    controller->keyRight.down = true;
                    break;

                case 1:
                    ControllerInfo->keyDown.down |= true;
                    controller->keyDown.down = true;
                    break;

                case 2:
                    ControllerInfo->keyLeft.down |= true;
                    controller->keyLeft.down = true;
                    break;

                case 3:
                    ControllerInfo->keyUp.down |= true;
                    controller->keyUp.down = true;
                    break;
            }
        }

        // fixes a bug with button vs touch
        bool32 touchedJump = false;
        if (CheckTouchRect(ScreenInfo->center.x, 96, ScreenInfo->size.x, ScreenInfo->size.y, NULL, NULL) >= 0) {
            ControllerInfo->keyA.down |= true;
            controller->keyA.down = true;
            touchedJump           = true;
        }

        bool32 touchedPause = false;
        if (CheckTouchRect(ScreenInfo->size.x - 0x80, 0, ScreenInfo->size.x, 0x40, NULL, NULL) >= 0) {
            ControllerInfo->keyStart.down |= true;
            controller->keyStart.down = true;
            touchedPause              = true;
        }
        
        bool32 touchedDebug = false;
        if (SceneInfo->debugMode) {
            if (CheckTouchRect(0, 0, 112, 56, NULL, NULL) >= 0) {
                ControllerInfo->keyX.down |= true;
                controller->keyX.down = true;
                touchedDebug          = true;
            }
        }

#if MANIA_USE_PLUS
        bool32 touchedSwap = false;
        if (globals->gameMode == MODE_ENCORE) {
            if (CheckTouchRect(ScreenInfo->size.x - 0x100, 0, ScreenInfo->size.x - 0x80, 0x40, NULL, NULL) >= 0) {
                ControllerInfo->keyY.down |= true;
                controller->keyY.down = true;
                touchedSwap           = true;
            }
        }

        if (!Mod_Player->touchSwap && touchedSwap) {
            ControllerInfo->keyY.press |= ControllerInfo->keyY.down;
            controller->keyY.press |= controller->keyY.down;
        }
        Mod_Player->touchSwap = controller->keyY.down;
#endif

        if (!Mod_Player->touchJump && touchedJump) {
            ControllerInfo->keyA.press |= ControllerInfo->keyA.down;
            controller->keyA.press |= controller->keyA.down;
        }
        Mod_Player->touchJump = controller->keyA.down;

        if (!Mod_Player->touchDebug && touchedDebug) {
            ControllerInfo->keyX.press |= ControllerInfo->keyX.down;
            controller->keyX.press |= controller->keyX.down;
        }
        Mod_Player->touchDebug = controller->keyX.down;

        if (!Mod_Player->touchPause && touchedPause) {
            ControllerInfo->keyStart.press |= ControllerInfo->keyStart.down;
            controller->keyStart.press |= controller->keyStart.down;
        }
        Mod_Player->touchPause = controller->keyStart.down;
    }

    return false;
}