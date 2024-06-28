#include "BSS_Player.h"

#include "../Helpers.h"

ObjectBSS_Player *BSS_Player;
ModObjectBSS_Player *Mod_BSS_Player;

// Public Functions
StateMachine(BSS_Player_Input_P1) = NULL;

bool32 BSS_Player_Input_P1_Hook(bool32 skippedState)
{
    RSDK_THIS(BSS_Player);

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
        if (CheckTouchRect(ScreenInfo->center.x - 0x80, 0, ScreenInfo->center.x + 80, 0x40, NULL, NULL) >= 0) {
            ControllerInfo->keyStart.down |= true;
            controller->keyStart.down = true;
            touchedPause              = true;
        }

        if (!Mod_BSS_Player->touchJump && touchedJump) {
            ControllerInfo->keyA.press |= ControllerInfo->keyA.down;
            controller->keyA.press |= controller->keyA.down;
        }
        Mod_BSS_Player->touchJump = controller->keyA.down;

        if (!Mod_BSS_Player->touchPause && touchedPause) {
            ControllerInfo->keyStart.press |= ControllerInfo->keyStart.down;
            controller->keyStart.press |= controller->keyStart.down;
        }
        Mod_BSS_Player->touchPause = controller->keyStart.down;
    }

    return false;
}