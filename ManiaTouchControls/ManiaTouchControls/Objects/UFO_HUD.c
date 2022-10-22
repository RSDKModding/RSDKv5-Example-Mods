#include "UFO_HUD.h"
#include "UFO_Player.h"
#include "../ModConfig.h"

ObjectUFO_HUD *UFO_HUD;
ModObjectUFO_HUD *Mod_UFO_HUD;

void UFO_HUD_DrawTouchControls(void)
{
    RSDK_THIS(UFO_HUD);

    EntityUFO_Player *player = RSDK_GET_ENTITY(SLOT_PLAYER1, UFO_Player);

    int32 alphaStore   = self->alpha;
    int32 inkStore     = self->inkEffect;
    int32 fxStore      = self->drawFX;
    Vector2 scaleStore = self->scale;

    Mod_UFO_HUD->dpadPos.x = TO_FIXED(config.moveDPadPos.x);
    Mod_UFO_HUD->dpadPos.y = TO_FIXED(config.moveDPadPos.y);

    Mod_UFO_HUD->actionPos.x = TO_FIXED(ScreenInfo[SceneInfo->currentScreenID].size.x + config.jumpDPadPos.x);
    Mod_UFO_HUD->actionPos.y = TO_FIXED(config.jumpDPadPos.y);

    Mod_UFO_HUD->pausePos.x = TO_FIXED(ScreenInfo[SceneInfo->currentScreenID].size.x - 64);
    Mod_UFO_HUD->pausePos.y = TO_FIXED(16);

    self->inkEffect = INK_ALPHA;
    self->drawFX    = FX_SCALE;

    int32 opacity = (int32)(0x100 * config.vDPadOpacity);
    self->scale.x = (int32)(0x200 * config.vDPadSize);
    self->scale.y = (int32)(0x200 * config.vDPadSize);

    bool32 enabled = player->stateInput == UFO_Player_Input_P1;
    if (enabled) {
        if ((SceneInfo->state & 3) == ENGINESTATE_REGULAR) {
            if (Mod_UFO_HUD->dpadAlpha < opacity) {
                Mod_UFO_HUD->dpadAlpha += 4;
                Mod_UFO_HUD->pauseAlpha = Mod_UFO_HUD->dpadAlpha << 1;
            }

            // Draw DPad
            self->alpha                   = Mod_UFO_HUD->dpadAlpha;
            Mod_UFO_HUD->dpadAnimator.frameID = 10;
            RSDK.DrawSprite(&Mod_UFO_HUD->dpadAnimator, &Mod_UFO_HUD->dpadPos, true);

            if (player->left) {
                self->alpha                        = opacity;
                Mod_UFO_HUD->dpadTouchAnimator.frameID = 6;
                RSDK.DrawSprite(&Mod_UFO_HUD->dpadTouchAnimator, &Mod_UFO_HUD->dpadPos, true);
            }
            else {
                self->alpha                   = Mod_UFO_HUD->dpadAlpha;
                Mod_UFO_HUD->dpadAnimator.frameID = 6;
                RSDK.DrawSprite(&Mod_UFO_HUD->dpadAnimator, &Mod_UFO_HUD->dpadPos, true);
            }

            if (player->down) {
                self->alpha                        = opacity;
                Mod_UFO_HUD->dpadTouchAnimator.frameID = 9;
                RSDK.DrawSprite(&Mod_UFO_HUD->dpadTouchAnimator, &Mod_UFO_HUD->dpadPos, true);
            }
            else {
                self->alpha                   = Mod_UFO_HUD->dpadAlpha;
                Mod_UFO_HUD->dpadAnimator.frameID = 9;
                RSDK.DrawSprite(&Mod_UFO_HUD->dpadAnimator, &Mod_UFO_HUD->dpadPos, true);
            }

            if (player->right) {
                self->alpha                        = opacity;
                Mod_UFO_HUD->dpadTouchAnimator.frameID = 7;
                RSDK.DrawSprite(&Mod_UFO_HUD->dpadTouchAnimator, &Mod_UFO_HUD->dpadPos, true);
            }
            else {
                self->alpha                   = Mod_UFO_HUD->dpadAlpha;
                Mod_UFO_HUD->dpadAnimator.frameID = 7;
                RSDK.DrawSprite(&Mod_UFO_HUD->dpadAnimator, &Mod_UFO_HUD->dpadPos, true);
            }

            if (player->up) {
                self->alpha                        = opacity;
                Mod_UFO_HUD->dpadTouchAnimator.frameID = 8;
                RSDK.DrawSprite(&Mod_UFO_HUD->dpadTouchAnimator, &Mod_UFO_HUD->dpadPos, true);
            }
            else {
                self->alpha                   = Mod_UFO_HUD->dpadAlpha;
                Mod_UFO_HUD->dpadAnimator.frameID = 8;
                RSDK.DrawSprite(&Mod_UFO_HUD->dpadAnimator, &Mod_UFO_HUD->dpadPos, true);
            }

            if (player->jumpHold) {
                self->alpha                        = opacity;
                Mod_UFO_HUD->dpadTouchAnimator.frameID = 1;
                RSDK.DrawSprite(&Mod_UFO_HUD->dpadTouchAnimator, &Mod_UFO_HUD->actionPos, true);
            }
            else {
                self->alpha                   = Mod_UFO_HUD->dpadAlpha;
                Mod_UFO_HUD->dpadAnimator.frameID = 1;
                RSDK.DrawSprite(&Mod_UFO_HUD->dpadAnimator, &Mod_UFO_HUD->actionPos, true);
            }
        }
        else {
            Mod_UFO_HUD->dpadAlpha  = 0;
            Mod_UFO_HUD->pauseAlpha = 0;
        }

        self->alpha                        = Mod_UFO_HUD->pauseAlpha;
        Mod_UFO_HUD->dpadTouchAnimator.frameID = 5;
        RSDK.DrawSprite(&Mod_UFO_HUD->dpadTouchAnimator, &Mod_UFO_HUD->pausePos, true);
    }
    else {
        if (Mod_UFO_HUD->dpadAlpha > 0) {
            Mod_UFO_HUD->dpadAlpha -= 4;
            Mod_UFO_HUD->pauseAlpha -= 8;
        }

        self->alpha = Mod_UFO_HUD->dpadAlpha;
        if (self->alpha > 0) {
            Mod_UFO_HUD->dpadAnimator.frameID = 0;
            RSDK.DrawSprite(&Mod_UFO_HUD->dpadAnimator, &Mod_UFO_HUD->dpadPos, true);

            Mod_UFO_HUD->dpadAnimator.frameID = 1;
            RSDK.DrawSprite(&Mod_UFO_HUD->dpadAnimator, &Mod_UFO_HUD->actionPos, true);
        }

        if (Mod_UFO_HUD->pauseAlpha < 0)
            self->alpha = 0;
        else
            self->alpha = Mod_UFO_HUD->pauseAlpha;

        Mod_UFO_HUD->dpadTouchAnimator.frameID = 5;
        RSDK.DrawSprite(&Mod_UFO_HUD->dpadTouchAnimator, &Mod_UFO_HUD->pausePos, true);
    }

    self->alpha     = alphaStore;
    self->inkEffect = inkStore;
    self->drawFX    = fxStore;
    self->scale     = scaleStore;
}

void UFO_HUD_Draw(void)
{
    RSDK_THIS(UFO_HUD);

    Mod.Super(UFO_HUD->classID, SUPER_DRAW, NULL);

    UFO_HUD_DrawTouchControls();
}

void UFO_HUD_StageLoad(void)
{
    Mod.Super(UFO_HUD->classID, SUPER_STAGELOAD, NULL);

    Mod_UFO_HUD->dpadFrames = RSDK.LoadSpriteAnimation("Global/TouchControls.bin", SCOPE_STAGE);

    RSDK.SetSpriteAnimation(Mod_UFO_HUD->dpadFrames, 0, &Mod_UFO_HUD->dpadAnimator, true, 0);
    RSDK.SetSpriteAnimation(Mod_UFO_HUD->dpadFrames, 1, &Mod_UFO_HUD->dpadTouchAnimator, true, 0);
}