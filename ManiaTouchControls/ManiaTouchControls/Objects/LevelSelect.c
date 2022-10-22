#include "LevelSelect.h"

#include "../ModConfig.h"
#include "../Helpers.h"

ObjectLevelSelect *LevelSelect;
ModObjectLevelSelect *Mod_LevelSelect;

bool32 LevelSelect_State_Navigate_Hook(bool32 skippedState)
{
    RSDK_THIS(LevelSelect);

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

    InputState *confirmButton = API_GetConfirmButtonFlip() ? &ControllerInfo->keyB : &ControllerInfo->keyA;

    int32 jumpX = ScreenInfo->size.x + config.jumpDPadPos.x - 48;
    int32 jumpY = config.jumpDPadPos.y - 48;

    // fixes a bug with button vs touch
    bool32 touchedConfirm = false;
    if (CheckTouchRect(jumpX, jumpY, ScreenInfo->size.x, ScreenInfo->size.y, NULL, NULL) >= 0) {
        confirmButton->down |= true;
        touchedConfirm = true;
    }

    bool32 touchedSwap = false;
    if (CheckTouchRect(jumpX, jumpY - 64, ScreenInfo->size.x, jumpY, NULL, NULL) >= 0) {
        ControllerInfo->keyX.down |= true;
        touchedSwap = true;
    }

    bool32 touchedSwapP2 = false;
    if (self->leaderCharacterID == LSELECT_PLAYER_SONIC) {
        if (CheckTouchRect(jumpX - 64, jumpY, jumpX, ScreenInfo->size.x, NULL, NULL) >= 0) {
            ControllerInfo->keyY.down |= true;
            touchedSwapP2 = true;
        }
    }

    if (dir != Mod_LevelSelect->touchDir && ControllerInfo->keyUp.down)
        ControllerInfo->keyUp.press |= ControllerInfo->keyUp.down;

    if (dir != Mod_LevelSelect->touchDir && ControllerInfo->keyDown.down)
        ControllerInfo->keyDown.press |= ControllerInfo->keyDown.down;

    if (dir != Mod_LevelSelect->touchDir && ControllerInfo->keyLeft.down)
        ControllerInfo->keyLeft.press |= ControllerInfo->keyLeft.down;

    if (dir != Mod_LevelSelect->touchDir && ControllerInfo->keyRight.down)
        ControllerInfo->keyRight.press |= ControllerInfo->keyRight.down;

    if (!Mod_LevelSelect->touchConfirm && touchedConfirm)
        confirmButton->press |= confirmButton->down;

    if (!Mod_LevelSelect->touchSwap && touchedSwap)
        ControllerInfo->keyX.press |= ControllerInfo->keyX.down;
    Mod_LevelSelect->touchSwap = ControllerInfo->keyX.down;

    if (!Mod_LevelSelect->touchSwapP2 && touchedSwapP2)
        ControllerInfo->keyY.press |= ControllerInfo->keyY.down;
    Mod_LevelSelect->touchSwapP2 = ControllerInfo->keyY.down;

    Mod_LevelSelect->touchConfirm = confirmButton->down;
    Mod_LevelSelect->touchDir     = dir;

    return false;
}

void LevelSelect_DrawUI(void)
{
    RSDK_THIS(LevelSelect);

    int32 alphaStore   = self->alpha;
    int32 inkStore     = self->inkEffect;
    int32 fxStore      = self->drawFX;
    Vector2 scaleStore = self->scale;

    Mod_LevelSelect->dpadPos.x = TO_FIXED(config.moveDPadPos.x);
    Mod_LevelSelect->dpadPos.y = TO_FIXED(config.moveDPadPos.y);

    Mod_LevelSelect->confirmPos.x = TO_FIXED(ScreenInfo[SceneInfo->currentScreenID].size.x + config.jumpDPadPos.x);
    Mod_LevelSelect->confirmPos.y = TO_FIXED(config.jumpDPadPos.y);

    Mod_LevelSelect->swapPos.x = Mod_LevelSelect->confirmPos.x;
    Mod_LevelSelect->swapPos.y = Mod_LevelSelect->confirmPos.y - TO_FIXED(64);

    Mod_LevelSelect->swapP2Pos.x = Mod_LevelSelect->confirmPos.x - TO_FIXED(64);
    Mod_LevelSelect->swapP2Pos.y = Mod_LevelSelect->confirmPos.y;

    self->inkEffect = INK_ALPHA;
    self->drawFX    = FX_SCALE;

    int32 opacity = (int32)(0x100 * config.vDPadOpacity);
    self->scale.x = (int32)(0x200 * config.vDPadSize);
    self->scale.y = (int32)(0x200 * config.vDPadSize);

    InputState *confirmButton = API_GetConfirmButtonFlip() ? &ControllerInfo->keyB : &ControllerInfo->keyA;

    bool32 canMove    = true;
    bool32 canConfirm = true;
    bool32 canSwap    = true;
    bool32 canSwapP2  = self->leaderCharacterID == LSELECT_PLAYER_SONIC;

    if (canMove) {
        if (Mod_LevelSelect->dpadAlpha < opacity)
            Mod_LevelSelect->dpadAlpha += 4;

        // Draw DPad
        self->alpha                       = Mod_LevelSelect->dpadAlpha;
        Mod_LevelSelect->dpadAnimator.frameID = 10;
        RSDK.DrawSprite(&Mod_LevelSelect->dpadAnimator, &Mod_LevelSelect->dpadPos, true);

        if (Mod_LevelSelect->touchDir == 2) {
            self->alpha                            = opacity;
            Mod_LevelSelect->dpadTouchAnimator.frameID = 6;
            RSDK.DrawSprite(&Mod_LevelSelect->dpadTouchAnimator, &Mod_LevelSelect->dpadPos, true);
        }
        else {
            self->alpha                       = Mod_LevelSelect->dpadAlpha;
            Mod_LevelSelect->dpadAnimator.frameID = 6;
            RSDK.DrawSprite(&Mod_LevelSelect->dpadAnimator, &Mod_LevelSelect->dpadPos, true);
        }

        if (Mod_LevelSelect->touchDir == 1) {
            self->alpha                            = opacity;
            Mod_LevelSelect->dpadTouchAnimator.frameID = 9;
            RSDK.DrawSprite(&Mod_LevelSelect->dpadTouchAnimator, &Mod_LevelSelect->dpadPos, true);
        }
        else {
            self->alpha                       = Mod_LevelSelect->dpadAlpha;
            Mod_LevelSelect->dpadAnimator.frameID = 9;
            RSDK.DrawSprite(&Mod_LevelSelect->dpadAnimator, &Mod_LevelSelect->dpadPos, true);
        }

        if (Mod_LevelSelect->touchDir == 0) {
            self->alpha                            = opacity;
            Mod_LevelSelect->dpadTouchAnimator.frameID = 7;
            RSDK.DrawSprite(&Mod_LevelSelect->dpadTouchAnimator, &Mod_LevelSelect->dpadPos, true);
        }
        else {
            self->alpha                       = Mod_LevelSelect->dpadAlpha;
            Mod_LevelSelect->dpadAnimator.frameID = 7;
            RSDK.DrawSprite(&Mod_LevelSelect->dpadAnimator, &Mod_LevelSelect->dpadPos, true);
        }

        if (Mod_LevelSelect->touchDir == 3) {
            self->alpha                            = opacity;
            Mod_LevelSelect->dpadTouchAnimator.frameID = 8;
            RSDK.DrawSprite(&Mod_LevelSelect->dpadTouchAnimator, &Mod_LevelSelect->dpadPos, true);
        }
        else {
            self->alpha                       = Mod_LevelSelect->dpadAlpha;
            Mod_LevelSelect->dpadAnimator.frameID = 8;
            RSDK.DrawSprite(&Mod_LevelSelect->dpadAnimator, &Mod_LevelSelect->dpadPos, true);
        }
    }
    else {
        if (Mod_LevelSelect->dpadAlpha > 0) {
            Mod_LevelSelect->dpadAlpha -= 4;
        }

        self->alpha = Mod_LevelSelect->dpadAlpha;
        if (self->alpha > 0) {
            Mod_LevelSelect->dpadAnimator.frameID = 0;
            RSDK.DrawSprite(&Mod_LevelSelect->dpadAnimator, &Mod_LevelSelect->dpadPos, true);
        }
    }

    if (canConfirm) {
        if ((SceneInfo->state & 3) == ENGINESTATE_REGULAR) {
            if (Mod_LevelSelect->confirmAlpha < opacity)
                Mod_LevelSelect->confirmAlpha += 4;

            if (confirmButton->down) {
                self->alpha                            = opacity;
                Mod_LevelSelect->dpadTouchAnimator.frameID = 1;
                RSDK.DrawSprite(&Mod_LevelSelect->dpadTouchAnimator, &Mod_LevelSelect->confirmPos, true);
            }
            else {
                self->alpha                       = Mod_LevelSelect->confirmAlpha;
                Mod_LevelSelect->dpadAnimator.frameID = 1;
                RSDK.DrawSprite(&Mod_LevelSelect->dpadAnimator, &Mod_LevelSelect->confirmPos, true);
            }
        }
        else {
            Mod_LevelSelect->confirmAlpha = 0;
        }
    }
    else {
        if (Mod_LevelSelect->confirmAlpha > 0)
            Mod_LevelSelect->confirmAlpha -= 4;

        self->alpha = Mod_LevelSelect->confirmAlpha;
        if (self->alpha > 0) {
            Mod_LevelSelect->dpadAnimator.frameID = 1;
            RSDK.DrawSprite(&Mod_LevelSelect->dpadAnimator, &Mod_LevelSelect->confirmPos, true);
        }
    }

    if (canSwap) {
        if ((SceneInfo->state & 3) == ENGINESTATE_REGULAR) {
            if (Mod_LevelSelect->swapAlpha < opacity)
                Mod_LevelSelect->swapAlpha += 4;

            if (ControllerInfo->keyX.down) {
                self->alpha                        = opacity;
                Mod_LevelSelect->dpadTouchAnimator.frameID = 4;
                RSDK.DrawSprite(&Mod_LevelSelect->dpadTouchAnimator, &Mod_LevelSelect->swapPos, true);
            }
            else {
                self->alpha                   = Mod_LevelSelect->swapAlpha;
                Mod_LevelSelect->dpadAnimator.frameID = 4;
                RSDK.DrawSprite(&Mod_LevelSelect->dpadAnimator, &Mod_LevelSelect->swapPos, true);
            }
        }
        else {
            Mod_LevelSelect->swapAlpha = 0;
        }
    }
    else {
        if (Mod_LevelSelect->swapAlpha > 0)
            Mod_LevelSelect->swapAlpha -= 4;

        self->alpha = Mod_LevelSelect->swapAlpha;
        if (self->alpha > 0) {
            Mod_LevelSelect->dpadAnimator.frameID = 4;
            RSDK.DrawSprite(&Mod_LevelSelect->dpadAnimator, &Mod_LevelSelect->swapPos, true);
        }
    }

    if (canSwapP2) {
        if ((SceneInfo->state & 3) == ENGINESTATE_REGULAR) {
            if (Mod_LevelSelect->swapP2Alpha < opacity)
                Mod_LevelSelect->swapP2Alpha += 4;

            if (ControllerInfo->keyY.down) {
                self->alpha                                = opacity;
                Mod_LevelSelect->dpadTouchAnimator.frameID = 4;
                RSDK.DrawSprite(&Mod_LevelSelect->dpadTouchAnimator, &Mod_LevelSelect->swapP2Pos, true);
            }
            else {
                self->alpha                           = Mod_LevelSelect->swapP2Alpha;
                Mod_LevelSelect->dpadAnimator.frameID = 4;
                RSDK.DrawSprite(&Mod_LevelSelect->dpadAnimator, &Mod_LevelSelect->swapP2Pos, true);
            }
        }
        else {
            Mod_LevelSelect->swapP2Alpha = 0;
        }
    }
    else {
        if (Mod_LevelSelect->swapP2Alpha > 0)
            Mod_LevelSelect->swapP2Alpha -= 4;

        self->alpha = Mod_LevelSelect->swapP2Alpha;
        if (self->alpha > 0) {
            Mod_LevelSelect->dpadAnimator.frameID = 4;
            RSDK.DrawSprite(&Mod_LevelSelect->dpadAnimator, &Mod_LevelSelect->swapP2Pos, true);
        }
    }

    self->alpha     = alphaStore;
    self->inkEffect = inkStore;
    self->drawFX    = fxStore;
    self->scale     = scaleStore;
}

void LevelSelect_Draw(void)
{
    LevelSelect_DrawUI();

    Mod.Super(LevelSelect->classID, SUPER_DRAW, NULL);
}

void LevelSelect_StageLoad(void)
{
    Mod.Super(LevelSelect->classID, SUPER_STAGELOAD, NULL);

    Mod_LevelSelect->dpadFrames = RSDK.LoadSpriteAnimation("Global/TouchControls.bin", SCOPE_STAGE);

    RSDK.SetSpriteAnimation(Mod_LevelSelect->dpadFrames, 0, &Mod_LevelSelect->dpadAnimator, true, 0);
    RSDK.SetSpriteAnimation(Mod_LevelSelect->dpadFrames, 1, &Mod_LevelSelect->dpadTouchAnimator, true, 0);

    Mod_LevelSelect->touchDir = -1;
}