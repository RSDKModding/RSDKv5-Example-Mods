#include "DASetup.h"
#include "UIControl.h"

#include "../ModConfig.h"
#include "../Helpers.h"

ObjectDASetup *DASetup;
ModObjectDASetup *Mod_DASetup;


bool32 DASetup_State_ManageControl_Hook(bool32 skippedState) {
    HandleDPad_4Dir(NULL);

    // fixes a bug with button vs touch
    bool32 touchedConfirm = false;
    if (CheckTouchRect(ScreenInfo->center.x, 96, ScreenInfo->size.x, ScreenInfo->size.y, NULL, NULL) >= 0) {
        ControllerInfo->keyA.down |= true;
        touchedConfirm = true;
    }

    if (!Mod_DASetup->touchConfirm && touchedConfirm)
        ControllerInfo->keyA.press |= ControllerInfo->keyA.down;

    Mod_DASetup->touchConfirm = ControllerInfo->keyA.down;

    if (CheckTouchPause())
        ControllerInfo->keyB.press |= true;

    UIControl->anyRightPress |= ControllerInfo->keyRight.press;
    UIControl->anyLeftPress |= ControllerInfo->keyLeft.press;
    UIControl->anyUpPress |= ControllerInfo->keyUp.press;
    UIControl->anyDownPress |= ControllerInfo->keyDown.press;
    UIControl->anyConfirmPress |= ControllerInfo->keyA.press;
    UIControl->anyBackPress |= ControllerInfo->keyB.press;

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

    Mod_DASetup->backPos.x = TO_FIXED(ScreenInfo[SceneInfo->currentScreenID].size.x - 25);
    Mod_DASetup->backPos.y = TO_FIXED(16);

    self->inkEffect = INK_ALPHA;
    self->drawFX    = FX_SCALE;

    int32 opacity = (int32)(0x100 * config.vDPadOpacity);
    self->scale.x = (int32)(0x200 * config.vDPadSize);
    self->scale.y = (int32)(0x200 * config.vDPadSize);

    if (Mod_DASetup->dpadAlpha < opacity)
        Mod_DASetup->dpadAlpha += 4;

    // Draw DPad
    self->alpha                       = Mod_DASetup->dpadAlpha;
    Mod_DASetup->dpadAnimator.frameID = 10;
    RSDK.DrawSprite(&Mod_DASetup->dpadAnimator, &Mod_DASetup->dpadPos, true);

    if (ControllerInfo->keyLeft.down) {
        self->alpha                            = opacity;
        Mod_DASetup->dpadTouchAnimator.frameID = 6;
        RSDK.DrawSprite(&Mod_DASetup->dpadTouchAnimator, &Mod_DASetup->dpadPos, true);
    }
    else {
        self->alpha                       = Mod_DASetup->dpadAlpha;
        Mod_DASetup->dpadAnimator.frameID = 6;
        RSDK.DrawSprite(&Mod_DASetup->dpadAnimator, &Mod_DASetup->dpadPos, true);
    }

    if (ControllerInfo->keyDown.down) {
        self->alpha                            = opacity;
        Mod_DASetup->dpadTouchAnimator.frameID = 9;
        RSDK.DrawSprite(&Mod_DASetup->dpadTouchAnimator, &Mod_DASetup->dpadPos, true);
    }
    else {
        self->alpha                       = Mod_DASetup->dpadAlpha;
        Mod_DASetup->dpadAnimator.frameID = 9;
        RSDK.DrawSprite(&Mod_DASetup->dpadAnimator, &Mod_DASetup->dpadPos, true);
    }

    if (ControllerInfo->keyRight.down) {
        self->alpha                            = opacity;
        Mod_DASetup->dpadTouchAnimator.frameID = 7;
        RSDK.DrawSprite(&Mod_DASetup->dpadTouchAnimator, &Mod_DASetup->dpadPos, true);
    }
    else {
        self->alpha                       = Mod_DASetup->dpadAlpha;
        Mod_DASetup->dpadAnimator.frameID = 7;
        RSDK.DrawSprite(&Mod_DASetup->dpadAnimator, &Mod_DASetup->dpadPos, true);
    }

    if (ControllerInfo->keyUp.down) {
        self->alpha                            = opacity;
        Mod_DASetup->dpadTouchAnimator.frameID = 8;
        RSDK.DrawSprite(&Mod_DASetup->dpadTouchAnimator, &Mod_DASetup->dpadPos, true);
    }
    else {
        self->alpha                       = Mod_DASetup->dpadAlpha;
        Mod_DASetup->dpadAnimator.frameID = 8;
        RSDK.DrawSprite(&Mod_DASetup->dpadAnimator, &Mod_DASetup->dpadPos, true);
    }

    if (!ControllerInfo->keyUp.down && !ControllerInfo->keyRight.down && !ControllerInfo->keyLeft.down && !ControllerInfo->keyRight.down) {
        self->alpha                       = Mod_DASetup->dpadAlpha;
        Mod_DASetup->dpadAnimator.frameID = 11;
        RSDK.DrawSprite(&Mod_DASetup->dpadAnimator, &Mod_DASetup->dpadPos, true);
    }

    int32 frameID = 1 + (DASetup->activeTrack == DASetup->trackID);

    if ((SceneInfo->state & 3) == ENGINESTATE_REGULAR) {
        if (ControllerInfo->keyA.down) {
            self->alpha                            = opacity;
            Mod_DASetup->dpadTouchAnimator.frameID = frameID;
            RSDK.DrawSprite(&Mod_DASetup->dpadTouchAnimator, &Mod_DASetup->playPos, true);
        }
        else {
            self->alpha                       = Mod_DASetup->dpadAlpha;
            Mod_DASetup->dpadAnimator.frameID = frameID;
            RSDK.DrawSprite(&Mod_DASetup->dpadAnimator, &Mod_DASetup->playPos, true);
        }

        if (ControllerInfo->keyB.down)
            self->alpha = opacity;
        else
            self->alpha = Mod_DASetup->dpadAlpha;
        Mod_DASetup->dpadArrowAnimator.frameID = 5;
        RSDK.DrawSprite(&Mod_DASetup->dpadArrowAnimator, &Mod_DASetup->backPos, true);
    }
    else {
        Mod_DASetup->dpadAlpha = 0;
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
    RSDK.SetSpriteAnimation(Mod_DASetup->dpadFrames, 2, &Mod_DASetup->dpadArrowAnimator, true, 0);
}