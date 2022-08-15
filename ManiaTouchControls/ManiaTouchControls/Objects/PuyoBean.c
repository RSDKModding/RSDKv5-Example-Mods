#include "PuyoBean.h"

#include "../ModConfig.h"
#include "../Helpers.h"

ObjectPuyoBean *PuyoBean;
ModObjectPuyoBean *Mod_PuyoBean;

bool32 PuyoBean_Input_Player_Hook(bool32 skippedState)
{
    RSDK_THIS(PuyoBean);

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
        int32 halfX        = ScreenInfo->center.x / 2;

        bool32 touchedRotR = false;
        if (CheckTouchRect(ScreenInfo->center.x, 96, ScreenInfo->center.x + halfX, ScreenInfo->size.y, NULL, NULL) >= 0) {
            ControllerInfo->keyA.down |= true;
            controller->keyA.down = true;
            touchedRotR           = true;
        }

        bool32 touchedRotL = false;
        if (CheckTouchRect(ScreenInfo->center.x + halfX, 96, ScreenInfo->size.x, ScreenInfo->size.y, NULL, NULL) >= 0) {
            ControllerInfo->keyB.down |= true;
            controller->keyB.down = true;
            touchedRotL           = true;
        }

        if (!Mod_PuyoBean->touchLeft && touchedRotL) {
            ControllerInfo->keyB.press |= ControllerInfo->keyB.down;
            controller->keyB.press |= controller->keyB.down;
        }

        if (!Mod_PuyoBean->touchRight && touchedRotR) {
            ControllerInfo->keyA.press |= ControllerInfo->keyA.down;
            controller->keyA.press |= controller->keyA.down;
        }

        Mod_PuyoBean->touchLeft  = controller->keyB.down;
        Mod_PuyoBean->touchRight = controller->keyA.down;

        if (CheckTouchRect(ScreenInfo->size.x - 0x80, 0, ScreenInfo->size.x, 0x40, NULL, NULL) >= 0) {
            ControllerInfo->keyStart.down |= true;
            controller->keyStart.down = true;
        }
    }

    return false;
}