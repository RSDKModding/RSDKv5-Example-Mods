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

        HandleDPad_4Dir(controller);

        // fixes a bug with button vs touch
        bool32 touched = false;

        int32 halfX = ScreenInfo->center.x / 2;

        if (CheckTouchRect(ScreenInfo->center.x, 96, ScreenInfo->center.x + halfX, ScreenInfo->size.y, NULL, NULL) >= 0) {
            ControllerInfo->keyB.down |= true;
            controller->keyB.down = true;
            touched               = true;
        }

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