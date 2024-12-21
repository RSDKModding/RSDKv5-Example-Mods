#include "PBL_Player.h"
#include "PBL_Crane.h"
#include "../Helpers.h"

#if MANIA_USE_PLUS
ObjectPBL_Player *PBL_Player;
ModObjectPBL_Player *Mod_PBL_Player;

// Public Functions
StateMachine(PBL_Player_Input_P1) = NULL;

bool32 PBL_Player_Input_P1_Hook(bool32 skippedState)
{
    RSDK_THIS(PBL_Player);

    if (self->controllerID < PLAYER_COUNT && !Mod_PBL_Crane->active) {
        RSDKControllerState *controller = &ControllerInfo[self->controllerID];

        HandleDPad_4Dir(controller);

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
        if (CheckTouchPause()) {
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
#endif
