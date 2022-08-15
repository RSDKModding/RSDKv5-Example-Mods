#include "PBL_Flipper.h"
#include "PBL_Crane.h"

#include "../Helpers.h"

#if MANIA_USE_PLUS
ObjectPBL_Flipper *PBL_Flipper;
ModObjectPBL_Flipper *Mod_PBL_Flipper;

void PBL_Flipper_StaticUpdate(void)
{
    if (!Mod_PBL_Crane->active) {
        RSDKControllerState *controller = &ControllerInfo[CONT_P1];

        int32 div = ScreenInfo->center.x / 3;

        bool32 touchedL = true;
        if (CheckTouchRect(ScreenInfo->center.x, 96, ScreenInfo->center.x + div, ScreenInfo->size.y, NULL, NULL) >= 0) {
            TriggerInfoL[CONT_P1].keyBumper.down |= true;
            TriggerInfoL->keyBumper.down = true;
            touchedL                     = true;
        }

        bool32 touchedB = true;
        if (CheckTouchRect(ScreenInfo->center.x + div, 96, ScreenInfo->center.x + (div * 2), ScreenInfo->size.y, NULL, NULL) >= 0) {
            ControllerInfo[CONT_P1].keyA.down |= true;
            ControllerInfo->keyA.down = true;
            touchedB                  = true;
        }

        bool32 touchedR = true;
        if (CheckTouchRect(ScreenInfo->center.x + (div * 2), 96, ScreenInfo->size.x, ScreenInfo->size.y, NULL, NULL) >= 0) {
            TriggerInfoR[CONT_P1].keyBumper.down |= true;
            TriggerInfoR->keyBumper.down = true;
            touchedR                     = true;
        }

        if (!Mod_PBL_Flipper->touchL && touchedL) {
            TriggerInfoL[CONT_P1].keyBumper.press |= TriggerInfoL[CONT_P1].keyBumper.down;
            TriggerInfoL->keyBumper.press |= TriggerInfoL->keyBumper.down;
        }
        Mod_PBL_Flipper->touchL = TriggerInfoL[CONT_P1].keyBumper.down;

        if (!Mod_PBL_Flipper->touchB && touchedB) {
            ControllerInfo[CONT_P1].keyA.press |= ControllerInfo[CONT_P1].keyA.down;
            ControllerInfo->keyA.press |= ControllerInfo->keyA.down;
        }
        Mod_PBL_Flipper->touchB = ControllerInfo[CONT_P1].keyStart.down;

        if (!Mod_PBL_Flipper->touchR && touchedL) {
            TriggerInfoR[CONT_P1].keyBumper.press |= TriggerInfoR[CONT_P1].keyBumper.down;
            TriggerInfoR->keyBumper.press |= TriggerInfoR->keyBumper.down;
        }
        Mod_PBL_Flipper->touchR = TriggerInfoR[CONT_P1].keyBumper.down;
    }

	Mod.Super(PBL_Flipper->classID, SUPER_STATICUPDATE, NULL); 
}

#endif
