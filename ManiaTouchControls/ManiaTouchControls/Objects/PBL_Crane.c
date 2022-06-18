#include "PBL_Crane.h"

#include "../ModConfig.h"
#include "../Helpers.h"

#if MANIA_USE_PLUS
ObjectPBL_Crane *PBL_Crane;
ModObjectPBL_Crane *Mod_PBL_Crane;

void PBL_Crane_Update(void)
{
    RSDK_THIS(PBL_Crane);

    if (self->type == PBL_CRANE_CRANE && self->state) {
        Mod_PBL_Crane->active = true;

        RSDKControllerState *controller = &ControllerInfo[CONT_P1];
        uint8 dir                       = -1;

        int32 tx = 0, ty = 0;
        if (CheckTouchRect(0, 96, ScreenInfo->centerX, ScreenInfo->height, &tx, &ty) >= 0) {
            tx -= config.moveDPadPos.x;
            ty -= config.moveDPadPos.y;

            switch (((RSDK.ATan2(tx, ty) + 32) & 0xFF) >> 6) {
                case 0:
                    ControllerInfo->keyRight.down |= true;
                    controller->keyRight.down = true;
                    dir                       = 0;
                    break;

                case 1: break;

                case 2:
                    ControllerInfo->keyLeft.down |= true;
                    controller->keyLeft.down = true;
                    dir                      = 2;
                    break;

                case 3: break;
            }
        }

        if (dir != Mod_PBL_Crane->touchDir && ControllerInfo->keyLeft.down) {
            ControllerInfo->keyLeft.press |= ControllerInfo->keyLeft.down;
            controller->keyLeft.press |= controller->keyLeft.down;
        }

        if (dir != Mod_PBL_Crane->touchDir && ControllerInfo->keyRight.down) {
            ControllerInfo->keyRight.press |= ControllerInfo->keyRight.down;
            controller->keyRight.press |= controller->keyRight.down;
        }

        Mod_PBL_Crane->touchDir = dir;

        // fixes a bug with button vs touch
        bool32 touchedJump = false;
        if (CheckTouchRect(ScreenInfo->centerX, 96, ScreenInfo->width, ScreenInfo->height, NULL, NULL) >= 0) {
            ControllerInfo->keyDown.down |= true;
            controller->keyDown.down = true;
            touchedJump              = true;
        }

        if (!Mod_PBL_Crane->touchDown && touchedJump) {
            ControllerInfo->keyDown.press |= ControllerInfo->keyDown.down;
            controller->keyDown.press |= controller->keyDown.down;
        }
        Mod_PBL_Crane->touchDown = controller->keyDown.down;
    }

    Mod.Super(PBL_Crane->classID, SUPER_UPDATE, NULL);

    if (self->type == PBL_CRANE_CRANE && !self->state) {
        Mod_PBL_Crane->active = false;
    }
}

#endif
