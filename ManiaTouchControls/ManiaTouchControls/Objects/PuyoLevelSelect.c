#include "PuyoLevelSelect.h"

#include "../ModConfig.h"
#include "../Helpers.h"

ObjectPuyoLevelSelect *PuyoLevelSelect;
ModObjectPuyoLevelSelect *Mod_PuyoLevelSelect;

void PuyoLevelSelect_Update(void)
{
    RSDK_THIS(PuyoLevelSelect);

    if (self->canSelectLevels) {
        self->visible = !self->ready;

        int32 controllerID = self->playerID + 1;

        RSDKControllerState *controller = &ControllerInfo[controllerID];

        // fixes a bug with button vs touch
        bool32 touched = false;

        int32 tx = 0, ty = 0;
        if (CheckTouchRect(0, 96, ScreenInfo->center.x, ScreenInfo->size.y, &tx, &ty) >= 0) {
            tx -= config.moveDPadPos.x;
            ty -= config.moveDPadPos.y;

            switch (((RSDK.ATan2(tx, ty) + 32) & 0xFF) >> 6) {
                case 0: break;

                case 1:
                    ControllerInfo->keyDown.down |= true;
                    controller->keyDown.down = true;
                    touched                  = true;
                    break;

                case 2: break;

                case 3:
                    ControllerInfo->keyUp.down |= true;
                    controller->keyUp.down = true;
                    touched                = true;
                    break;
            }
        }

        if (!GET_BIT(Mod_PuyoLevelSelect->touchFlags, 0) && touched) {
            ControllerInfo->keyUp.press |= ControllerInfo->keyUp.down;
            controller->keyUp.press |= controller->keyUp.down;
        }

        if (!GET_BIT(Mod_PuyoLevelSelect->touchFlags, 1) && touched) {
            ControllerInfo->keyDown.press |= ControllerInfo->keyDown.down;
            controller->keyDown.press |= controller->keyDown.down;
        }
        SET_BIT(Mod_PuyoLevelSelect->touchFlags, controller->keyUp.down, 0);
        SET_BIT(Mod_PuyoLevelSelect->touchFlags, controller->keyDown.down, 1);

        int32 halfX = ScreenInfo->center.x / 2;

        bool32 touchedJump = false;
        if (CheckTouchRect(ScreenInfo->center.x, 96, ScreenInfo->center.x + halfX, ScreenInfo->size.y, NULL, NULL) >= 0) {
            ControllerInfo->keyB.down |= true;
            controller->keyB.down = true;
            touched               = true;
        }

        bool32 touchedPause = false;
        if (CheckTouchRect(ScreenInfo->center.x + halfX, 96, ScreenInfo->size.x, ScreenInfo->size.y, NULL, NULL) >= 0) {
            ControllerInfo->keyA.down |= true;
            controller->keyA.down = true;
            touched               = true;
        }

        if (!GET_BIT(Mod_PuyoLevelSelect->touchFlags, 2) && touched) {
            ControllerInfo->keyA.press |= ControllerInfo->keyA.down;
            controller->keyA.press |= controller->keyA.down;
        }

        if (!GET_BIT(Mod_PuyoLevelSelect->touchFlags, 3) && touched) {
            ControllerInfo->keyB.press |= ControllerInfo->keyB.down;
            controller->keyB.press |= controller->keyB.down;
        }

        SET_BIT(Mod_PuyoLevelSelect->touchFlags, controller->keyA.down, 2);
        SET_BIT(Mod_PuyoLevelSelect->touchFlags, controller->keyB.down, 3);
    }

    Mod.Super(PuyoLevelSelect->classID, SUPER_UPDATE, NULL);
}