#include "TimeAttackGate.h"
#include "../ModConfig.h"
#include "../Helpers.h"

ObjectTimeAttackGate *TimeAttackGate;
ModObjectTimeAttackGate *Mod_TimeAttackGate;

bool32 TimeAttackGate_State_Restarter_Hook(bool32 skippedState)
{
    RSDK_THIS(TimeAttackGate);

    if (TimeAttackGate->isFinished)
        return false;
    else {
        EntityPlayer *player = TimeAttackGate->triggerPlayer;

        if (player) {
            if (player->state == Player_State_Death || player->state == Player_State_Drown)
                return false;
            else {
                RSDKControllerState *controller = &ControllerInfo[player->controllerID];

                bool32 canRestart = TimeAttackGate->started;

                int32 jumpX = ScreenInfo->center.x;
                int32 jumpY = config.jumpDPadPos.y - 48;

                bool32 touchedRestart = false;
                if (canRestart) {
                    if (CheckTouchRect(jumpX, jumpY - 64, ScreenInfo->size.x, jumpY, NULL, NULL) >= 0) {
                        ControllerInfo->keyY.down |= true;
                        controller->keyY.down    = true;
                        touchedRestart           = true;
                    }

                    if (!Mod_TimeAttackGate->touchRestart && touchedRestart) {
                        ControllerInfo->keyY.press |= ControllerInfo->keyY.down;
                        controller->keyY.press |= controller->keyY.down;
                    }
                    Mod_TimeAttackGate->touchRestart = controller->keyY.down;
                }
                else {
                    Mod_TimeAttackGate->touchRestart = 0;
                }
            }
        }
    }

    return false;
}
