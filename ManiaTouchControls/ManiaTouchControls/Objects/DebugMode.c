#include "DebugMode.h"
#include "Player.h"

#include "../Helpers.h"

ObjectDebugMode *DebugMode;

void DebugMode_Update(void)
{
    RSDK_THIS(DebugMode);

    RSDKControllerState *controller = &ControllerInfo[CONT_P1];

    HandleDPad_8Dir(controller);

    if (DebugMode->itemType == 0xFF)
        DebugMode->itemType = DebugMode->itemTypeCount ? (DebugMode->itemTypeCount - 1) : 0;

    int32 tx = 0, ty = 0;
    if (CheckTouchRect(ScreenInfo->center.x - 48, 0, ScreenInfo->center.x + 48, 56, &tx, &ty) >= 0) {
        if (tx > ScreenInfo->center.x) {
            if (!Mod_Player->touchJump) {
                DebugMode->itemType++;
                if (DebugMode->itemType >= DebugMode->itemTypeCount) {
                    DebugMode->itemType      = 0;
                    DebugMode->itemTypeCount = 0;

                    DebugMode->itemID++;
                    if (DebugMode->itemID >= DebugMode->itemCount)
                        DebugMode->itemID = 0;
                }
            }

            Mod_Player->touchJump = true;
        }
        else {
            if (!Mod_Player->touchJump) {
                DebugMode->itemType--;

                if (DebugMode->itemType == 0xFF) {
                    DebugMode->itemTypeCount = 0;

                    DebugMode->itemID--;
                    if (DebugMode->itemID < 0)
                        DebugMode->itemID = DebugMode->itemCount - 1;
                }
            }

            Mod_Player->touchJump = true;
        }
    }
    else {
        switch (CheckTouchRect(ScreenInfo->center.x, 96, ScreenInfo->size.x, SCREEN_YSIZE, NULL, NULL)) {
            case -1: Mod_Player->touchJump = false; break;

            case 0:
                ControllerInfo->keyC.down = true;
                controller->keyC.down     = true;
                if (!Mod_Player->touchJump) {
                    ControllerInfo->keyC.press = true;
                    controller->keyC.press     = true;
                }
                Mod_Player->touchJump = controller->keyC.down;
                break;
        }
    }

    bool32 touchedDebug = false;
    if (CheckTouchRect(0, 0, 112, 56, NULL, NULL) >= 0) {
#if GAME_VERSION != VER_100
        ControllerInfo->keyX.down = true;
        controller->keyX.down     = true;
#else
        ControllerInfo->keyY.down  = true;
        controller->keyY.down      = true;
#endif
        touchedDebug = true;
    }

    if (!Mod_Player->touchDebug && touchedDebug) {
#if GAME_VERSION != VER_100
        ControllerInfo->keyX.press = true;
        controller->keyX.press     = true;
#else
        ControllerInfo->keyY.press = true;
        controller->keyY.press     = true;
#endif
    }
#if GAME_VERSION != VER_100
    Mod_Player->touchDebug = controller->keyX.down;
#else
    Mod_Player->touchDebug = controller->keyY.down;
#endif

    if (CheckTouchRect(ScreenInfo->size.x - 88, 0, ScreenInfo->size.x, 40, NULL, NULL) >= 0 || controller->keyStart.press || Unknown_pausePress) {
        if (SceneInfo->state == ENGINESTATE_REGULAR) {
            // fuck it, TODO: this
            // EntityPauseMenu *pauseMenu = RSDK_GET_ENTITY(SLOT_PAUSEMENU);
            // bool32 allowPause          = true;
            //
            // if (ActClear && ActClear->actClearActive)
            //     allowPause = false;
            //
            // if (!RSDK.GetEntityCount(TitleCard->classID, false) && !pauseMenu->classID && allowPause) {
            //     RSDK.ResetEntitySlot(SLOT_PAUSEMENU, PauseMenu->classID, NULL);
            //     pauseMenu->triggerPlayer = self->playerID;
            //     if (globals->gameMode == MODE_COMPETITION)
            //         pauseMenu->disableRestart = true;
            // }
        }
    }

    Mod.Super(DebugMode->classID, SUPER_UPDATE, NULL);
}