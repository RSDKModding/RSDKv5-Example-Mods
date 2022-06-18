#include "DASetup.h"
#include "UIControl.h"

#include "../ModConfig.h"
#include "../Helpers.h"

ObjectDASetup *DASetup;
ModObjectDASetup *Mod_DASetup;


bool32 DASetup_State_ManageControl_Hook(bool32 skippedState) {
    uint8 dir = -1;

    int32 tx = 0, ty = 0;
    if (CheckTouchRect(0, 96, ScreenInfo->centerX, ScreenInfo->height, &tx, &ty) >= 0) {
        tx -= config.moveDPadPos.x;
        ty -= config.moveDPadPos.y;

        switch (((RSDK.ATan2(tx, ty) + 32) & 0xFF) >> 6) {
            case 0:
                ControllerInfo->keyRight.down |= true;
                dir = 0;
                break;

            case 1:
                ControllerInfo->keyDown.down |= true;
                dir = 1;
                break;

            case 2:
                ControllerInfo->keyLeft.down |= true;
                dir = 2;
                break;

            case 3:
                ControllerInfo->keyUp.down |= true;
                dir = 3;
                break;
        }
    }

    // fixes a bug with button vs touch
    bool32 touchedConfirm = false;
    if (CheckTouchRect(ScreenInfo->centerX, 96, ScreenInfo->width, ScreenInfo->height, NULL, NULL) >= 0) {
        ControllerInfo->keyA.down |= true;
        touchedConfirm = true;
    }

    bool32 touchedBack = false;
    if (CheckTouchRect(ScreenInfo->centerX, 0, ScreenInfo->width, 96, NULL, NULL) >= 0) {
        ControllerInfo->keyB.down |= true;
        touchedBack = true;
    }

    if (dir != Mod_DASetup->touchDir && ControllerInfo->keyUp.down)
        ControllerInfo->keyUp.press |= ControllerInfo->keyUp.down;

    if (dir != Mod_DASetup->touchDir && ControllerInfo->keyDown.down)
        ControllerInfo->keyDown.press |= ControllerInfo->keyDown.down;

    if (dir != Mod_DASetup->touchDir && ControllerInfo->keyLeft.down)
        ControllerInfo->keyLeft.press |= ControllerInfo->keyLeft.down;

    if (dir != Mod_DASetup->touchDir && ControllerInfo->keyRight.down)
        ControllerInfo->keyRight.press |= ControllerInfo->keyRight.down;

    if (!Mod_DASetup->touchConfirm && touchedConfirm)
        ControllerInfo->keyA.press |= ControllerInfo->keyA.down;
    if (!Mod_DASetup->touchBack && touchedBack)
        ControllerInfo->keyB.press |= ControllerInfo->keyB.down;

    Mod_DASetup->touchConfirm = ControllerInfo->keyA.down;
    Mod_DASetup->touchBack    = ControllerInfo->keyB.down;
    Mod_DASetup->touchDir     = dir;

    UIControl->anyRightPress |= ControllerInfo->keyRight.press;
    UIControl->anyLeftPress |= ControllerInfo->keyLeft.press;
    UIControl->anyUpPress |= ControllerInfo->keyUp.press;
    UIControl->anyDownPress |= ControllerInfo->keyDown.press;
    UIControl->anyConfirmPress |= ControllerInfo->keyA.press;
    UIControl->anyBackPress |= ControllerInfo->keyB.press;

    return false;
}