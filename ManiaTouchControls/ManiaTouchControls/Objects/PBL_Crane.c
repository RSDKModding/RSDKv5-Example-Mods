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

        HandleDPad_4Dir(controller);

        // fixes a bug with button vs touch
        bool32 touchedJump = false;
        if (CheckTouchRect(ScreenInfo->center.x, 96, ScreenInfo->size.x, ScreenInfo->size.y, NULL, NULL) >= 0) {
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
