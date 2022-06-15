#include "UFO_Player.h"
#include "../ModConfig.h"

bool32 UFO_Player_Input_P1_Hook(bool32 skippedState)
{
    RSDK_THIS(UFO_Player);

    if (self->controllerID < PLAYER_COUNT) {
        RSDKControllerState *controller = &ControllerInfo[self->controllerID];

        for (int32 t = 0; t < TouchInfo->count; ++t) {
            int32 tx = (int32)(TouchInfo->x[t] * ScreenInfo->width);
            int32 ty = (int32)(TouchInfo->y[t] * ScreenInfo->height);

            if (TouchInfo->down[t]) {
                if (tx >= 0 && ty >= 96 && tx <= ScreenInfo->centerX && ty <= ScreenInfo->height) {
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
                    break;
                }
            }
        }

        // fixes a bug with button vs touch
        bool32 touchedJump = false;
        for (int32 t = 0; t < TouchInfo->count; ++t) {
            int32 tx = (int32)(TouchInfo->x[t] * ScreenInfo->width);
            int32 ty = (int32)(TouchInfo->y[t] * ScreenInfo->height);

            if (TouchInfo->down[t]) {
                if (tx >= ScreenInfo->centerX && ty >= 96 && tx <= ScreenInfo->width && ty <= ScreenInfo->height) {
                    ControllerInfo->keyA.down |= true;
                    controller->keyA.down = true;
                    touchedJump           = true;
                    break;
                }
            }
        }

        bool32 touchedPause = false;
        for (int32 t = 0; t < TouchInfo->count; ++t) {
            int32 tx = (int32)(TouchInfo->x[t] * ScreenInfo->width);
            int32 ty = (int32)(TouchInfo->y[t] * ScreenInfo->height);

            if (TouchInfo->down[t]) {
                if (tx >= ScreenInfo->width - 0x80 && ty >= 0 && tx <= ScreenInfo->width && ty <= 0x40) {
                    if (SceneInfo->state == ENGINESTATE_REGULAR) {
                        ControllerInfo->keyStart.down |= true;
                        controller->keyStart.down = true;
                        touchedPause              = true;
                    }
                    break;
                }
            }
        }

        if (!self->touchJump && touchedJump) {
            ControllerInfo->keyA.press |= ControllerInfo->keyA.down;
            controller->keyA.press |= controller->keyA.down;
        }
        self->touchJump = controller->keyA.down;

        if (!self->touchPause && touchedPause) {
            ControllerInfo->keyStart.press |= ControllerInfo->keyStart.down;
            controller->keyStart.press |= controller->keyStart.down;
        }
        self->touchPause = controller->keyStart.down;
    }

    return false;
}