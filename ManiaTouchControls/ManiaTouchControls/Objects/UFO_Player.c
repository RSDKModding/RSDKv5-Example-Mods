#include "UFO_Player.h"

#include "../Helpers.h"

ObjectUFO_Player *UFO_Player;
ModObjectUFO_Player *Mod_UFO_Player;

// Public Functions
StateMachine(UFO_Player_Input_P1) = NULL;

bool32 UFO_Player_Input_P1_Hook(bool32 skippedState)
{
    RSDK_THIS(UFO_Player);

    if (self->controllerID < PLAYER_COUNT) {
        RSDKControllerState *controller = &ControllerInfo[self->controllerID];

        HandleDPad_4Dir(controller);

        // fixes a bug with button vs touch
        bool32 touchedJump = false;
        if (CheckTouchRect(ScreenInfo->center.x, 96, ScreenInfo->size.x, ScreenInfo->size.y, NULL, NULL) >= 0) {
            ControllerInfo->keyA.down |= true;
            controller->keyA.down = true;
            touchedJump           = true;
        }

        bool32 touchedPause = false;
        if (CheckTouchPause()) {
            ControllerInfo->keyStart.down |= true;
            controller->keyStart.down = true;
            touchedPause              = true;
        }

        if (!Mod_UFO_Player->touchJump && touchedJump) {
            ControllerInfo->keyA.press |= ControllerInfo->keyA.down;
            controller->keyA.press |= controller->keyA.down;
        }
        Mod_UFO_Player->touchJump = controller->keyA.down;

        if (!Mod_UFO_Player->touchPause && touchedPause) {
            ControllerInfo->keyStart.press |= ControllerInfo->keyStart.down;
            controller->keyStart.press |= controller->keyStart.down;
        }
        Mod_UFO_Player->touchPause = controller->keyStart.down;
    }

    return false;
}