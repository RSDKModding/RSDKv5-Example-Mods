#include "PBL_Player.h"
#include "PBL_Crane.h"

#include "../ModConfig.h"
#include "../Helpers.h"

ObjectPBL_Player *PBL_Player;
ModObjectPBL_Player *Mod_PBL_Player;

bool32 PBL_Player_Input_P1_Hook(bool32 skippedState)
{
    RSDK_THIS(PBL_Player);

    if (self->controllerID < PLAYER_COUNT && !Mod_PBL_Crane->active) {
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
        // bool32 touchedJump = false;
        // if (CheckTouchRect(ScreenInfo->center.x, 96, ScreenInfo->size.x, ScreenInfo->size.y, NULL, NULL) >= 0) {
        //     ControllerInfo->keyA.down |= true;
        //     controller->keyA.down = true;
        //     touchedJump           = true;
        // }
        //
        // if (!Mod_PBL_Player->touchJump && touchedJump) {
        //     ControllerInfo->keyA.press |= ControllerInfo->keyA.down;
        //     controller->keyA.press |= controller->keyA.down;
        // }
        // Mod_PBL_Player->touchJump = controller->keyA.down;

        bool32 touchedPause = false;
        if (CheckTouchRect(ScreenInfo->size.x - 0x80, 0, ScreenInfo->size.x, 0x40, NULL, NULL) >= 0) {
            ControllerInfo->keyStart.down |= true;
            controller->keyStart.down = true;
            touchedPause              = true;
        }

        if (!Mod_PBL_Player->touchPause && touchedPause) {
            ControllerInfo->keyStart.press |= ControllerInfo->keyStart.down;
            controller->keyStart.press |= controller->keyStart.down;
        }
        Mod_PBL_Player->touchPause = controller->keyStart.down;
    }

    return false;
}