#include "DASetup.h"
#include "UIControl.h"

#include "../ModConfig.h"
#include "../Helpers.h"

ObjectDASetup *DASetup;
ModObjectDASetup *Mod_DASetup;


bool32 DASetup_State_ManageControl_Hook(bool32 skippedState) {
    uint8 dir = -1;

    int32 tx = 0, ty = 0;
    if (CheckTouchRect(0, 96, ScreenInfo->center.x, ScreenInfo->size.y, &tx, &ty) >= 0) {
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
    if (CheckTouchRect(ScreenInfo->center.x, 96, ScreenInfo->size.x, ScreenInfo->size.y, NULL, NULL) >= 0) {
        ControllerInfo->keyA.down |= true;
        touchedConfirm = true;
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

    Mod_DASetup->touchConfirm = ControllerInfo->keyA.down;
    Mod_DASetup->touchDir     = dir;

    UIControl->anyRightPress |= ControllerInfo->keyRight.press;
    UIControl->anyLeftPress |= ControllerInfo->keyLeft.press;
    UIControl->anyUpPress |= ControllerInfo->keyUp.press;
    UIControl->anyDownPress |= ControllerInfo->keyDown.press;
    UIControl->anyConfirmPress |= ControllerInfo->keyA.press;

    return false;
}

void DASetup_ModCB_OnDraw(void *data)
{
    int32 group = VOID_TO_INT(data);

    if (DASetup && group == DRAWGROUP_COUNT - 1)
        DASetup_DrawUI();
}

void DASetup_DrawUI(void)
{
    RSDK_THIS(DASetup);

    int32 alphaStore   = self->alpha;
    int32 inkStore     = self->inkEffect;
    int32 fxStore      = self->drawFX;
    Vector2 scaleStore = self->scale;

    Mod_DASetup->dpadPos.x = TO_FIXED(config.moveDPadPos.x);
    Mod_DASetup->dpadPos.y = TO_FIXED(config.moveDPadPos.y);

    Mod_DASetup->playPos.x = TO_FIXED(ScreenInfo[SceneInfo->currentScreenID].size.x + config.jumpDPadPos.x);
    Mod_DASetup->playPos.y = TO_FIXED(config.jumpDPadPos.y);

    self->inkEffect = INK_ALPHA;
    self->drawFX    = FX_SCALE;

    int32 opacity = (int32)(0x100 * config.vDPadOpacity);
    self->scale.x = (int32)(0x200 * config.vDPadSize);
    self->scale.y = (int32)(0x200 * config.vDPadSize);

    bool32 canMove    = true;
    bool32 canPlay = true;
    bool32 canBack    = true;

    if (canMove) {
        if (Mod_DASetup->dpadAlpha < opacity)
            Mod_DASetup->dpadAlpha += 4;

        // Draw DPad
        self->alpha                         = Mod_DASetup->dpadAlpha;
        Mod_DASetup->dpadAnimator.frameID = 10;
        RSDK.DrawSprite(&Mod_DASetup->dpadAnimator, &Mod_DASetup->dpadPos, true);

        if (Mod_DASetup->touchDir == 2) {
            self->alpha                              = opacity;
            Mod_DASetup->dpadTouchAnimator.frameID = 6;
            RSDK.DrawSprite(&Mod_DASetup->dpadTouchAnimator, &Mod_DASetup->dpadPos, true);
        }
        else {
            self->alpha                         = Mod_DASetup->dpadAlpha;
            Mod_DASetup->dpadAnimator.frameID = 6;
            RSDK.DrawSprite(&Mod_DASetup->dpadAnimator, &Mod_DASetup->dpadPos, true);
        }

        if (Mod_DASetup->touchDir == 1) {
            self->alpha                              = opacity;
            Mod_DASetup->dpadTouchAnimator.frameID = 9;
            RSDK.DrawSprite(&Mod_DASetup->dpadTouchAnimator, &Mod_DASetup->dpadPos, true);
        }
        else {
            self->alpha                         = Mod_DASetup->dpadAlpha;
            Mod_DASetup->dpadAnimator.frameID = 9;
            RSDK.DrawSprite(&Mod_DASetup->dpadAnimator, &Mod_DASetup->dpadPos, true);
        }

        if (Mod_DASetup->touchDir == 0) {
            self->alpha                              = opacity;
            Mod_DASetup->dpadTouchAnimator.frameID = 7;
            RSDK.DrawSprite(&Mod_DASetup->dpadTouchAnimator, &Mod_DASetup->dpadPos, true);
        }
        else {
            self->alpha                         = Mod_DASetup->dpadAlpha;
            Mod_DASetup->dpadAnimator.frameID = 7;
            RSDK.DrawSprite(&Mod_DASetup->dpadAnimator, &Mod_DASetup->dpadPos, true);
        }

        if (Mod_DASetup->touchDir == 3) {
            self->alpha                              = opacity;
            Mod_DASetup->dpadTouchAnimator.frameID = 8;
            RSDK.DrawSprite(&Mod_DASetup->dpadTouchAnimator, &Mod_DASetup->dpadPos, true);
        }
        else {
            self->alpha                         = Mod_DASetup->dpadAlpha;
            Mod_DASetup->dpadAnimator.frameID = 8;
            RSDK.DrawSprite(&Mod_DASetup->dpadAnimator, &Mod_DASetup->dpadPos, true);
        }
    }
    else {
        if (Mod_DASetup->dpadAlpha > 0) {
            Mod_DASetup->dpadAlpha -= 4;
        }

        self->alpha = Mod_DASetup->dpadAlpha;
        if (self->alpha > 0) {
            Mod_DASetup->dpadAnimator.frameID = 0;
            RSDK.DrawSprite(&Mod_DASetup->dpadAnimator, &Mod_DASetup->dpadPos, true);
        }
    }

    int32 frameID = 1 + (DASetup->activeTrack == DASetup->trackID);
    if (canPlay) {
        if ((SceneInfo->state & 3) == ENGINESTATE_REGULAR) {
            if (Mod_DASetup->playAlpha < opacity)
                Mod_DASetup->playAlpha += 4;

            if (ControllerInfo->keyA.down) {
                self->alpha                              = opacity;
                Mod_DASetup->dpadTouchAnimator.frameID = frameID;
                RSDK.DrawSprite(&Mod_DASetup->dpadTouchAnimator, &Mod_DASetup->playPos, true);
            }
            else {
                self->alpha                         = Mod_DASetup->playAlpha;
                Mod_DASetup->dpadAnimator.frameID = frameID;
                RSDK.DrawSprite(&Mod_DASetup->dpadAnimator, &Mod_DASetup->playPos, true);
            }
        }
        else {
            Mod_DASetup->playAlpha = 0;
        }
    }
    else {
        if (Mod_DASetup->playAlpha > 0)
            Mod_DASetup->playAlpha -= 4;

        self->alpha = Mod_DASetup->playAlpha;
        if (self->alpha > 0) {
            Mod_DASetup->dpadAnimator.frameID = frameID;
            RSDK.DrawSprite(&Mod_DASetup->dpadAnimator, &Mod_DASetup->playPos, true);
        }
    }

    self->alpha     = alphaStore;
    self->inkEffect = inkStore;
    self->drawFX    = fxStore;
    self->scale     = scaleStore;
}

void DASetup_StageLoad(void)
{
    Mod.Super(DASetup->classID, SUPER_STAGELOAD, NULL);

    Mod_DASetup->dpadFrames = RSDK.LoadSpriteAnimation("Global/TouchControls.bin", SCOPE_STAGE);

    RSDK.SetSpriteAnimation(Mod_DASetup->dpadFrames, 0, &Mod_DASetup->dpadAnimator, true, 0);
    RSDK.SetSpriteAnimation(Mod_DASetup->dpadFrames, 1, &Mod_DASetup->dpadTouchAnimator, true, 0);

    Mod_DASetup->touchDir = -1;
}