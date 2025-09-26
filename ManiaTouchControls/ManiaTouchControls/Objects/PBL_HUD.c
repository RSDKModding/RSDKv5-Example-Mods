#include "PBL_HUD.h"
#include "PBL_Player.h"
#include "../ModConfig.h"

#if MANIA_USE_PLUS
ObjectPBL_HUD *PBL_HUD;
ModObjectPBL_HUD *Mod_PBL_HUD;

void PBL_HUD_DrawTouchControls(void)
{
    RSDK_THIS(PBL_HUD);

    EntityPBL_Player *player = NULL;
    foreach_active(PBL_Player, playerPtr)
    {
        player = playerPtr;
        foreach_break;
    }

    if (!player)
        return;

    int32 alphaStore   = self->alpha;
    int32 inkStore     = self->inkEffect;
    int32 fxStore      = self->drawFX;
    Vector2 scaleStore = self->scale;

    Mod_PBL_HUD->dpadPos.x = TO_FIXED(config.moveDPadPos.x);
    Mod_PBL_HUD->dpadPos.y = TO_FIXED(config.moveDPadPos.y);

    Mod_PBL_HUD->actionPos.x = TO_FIXED(ScreenInfo[SceneInfo->currentScreenID].size.x + config.jumpDPadPos.x);
    Mod_PBL_HUD->actionPos.y = TO_FIXED(config.jumpDPadPos.y);

    Mod_PBL_HUD->pausePos.x = TO_FIXED(ScreenInfo[SceneInfo->currentScreenID].size.x - 64);
    Mod_PBL_HUD->pausePos.y = TO_FIXED(16);

    self->inkEffect = INK_ALPHA;
    self->drawFX    = FX_SCALE;

    int32 opacity = (int32)(0x100 * config.vDPadOpacity);
    self->scale.x = (int32)(0x200 * config.vDPadSize);
    self->scale.y = (int32)(0x200 * config.vDPadSize);

    bool32 enabled = player->stateInput == PBL_Player_Input_P1;
    if (enabled) {
        if ((SceneInfo->state & 3) == ENGINESTATE_REGULAR) {
            if (Mod_PBL_HUD->dpadAlpha < opacity) {
                Mod_PBL_HUD->dpadAlpha += 4;
                Mod_PBL_HUD->pauseAlpha = Mod_PBL_HUD->dpadAlpha << 1;
            }

            // Draw DPad
            self->alpha                       = Mod_PBL_HUD->dpadAlpha;
            Mod_PBL_HUD->dpadAnimator.frameID = 10;
            RSDK.DrawSprite(&Mod_PBL_HUD->dpadAnimator, &Mod_PBL_HUD->dpadPos, true);

            if (player->left) {
                self->alpha                            = opacity;
                Mod_PBL_HUD->dpadTouchAnimator.frameID = 6;
                RSDK.DrawSprite(&Mod_PBL_HUD->dpadTouchAnimator, &Mod_PBL_HUD->dpadPos, true);
            }
            else {
                self->alpha                       = Mod_PBL_HUD->dpadAlpha;
                Mod_PBL_HUD->dpadAnimator.frameID = 6;
                RSDK.DrawSprite(&Mod_PBL_HUD->dpadAnimator, &Mod_PBL_HUD->dpadPos, true);
            }

            if (player->down) {
                self->alpha                            = opacity;
                Mod_PBL_HUD->dpadTouchAnimator.frameID = 9;
                RSDK.DrawSprite(&Mod_PBL_HUD->dpadTouchAnimator, &Mod_PBL_HUD->dpadPos, true);

                if (player->left) {
                    Mod_PBL_HUD->dpadTouchAnimator.frameID = 14;
                    RSDK.DrawSprite(&Mod_PBL_HUD->dpadTouchAnimator, &Mod_PBL_HUD->dpadPos, true);
                }
                else if (player->right) {
                    Mod_PBL_HUD->dpadTouchAnimator.frameID = 15;
                    RSDK.DrawSprite(&Mod_PBL_HUD->dpadTouchAnimator, &Mod_PBL_HUD->dpadPos, true);
                }
            }
            else {
                self->alpha                       = Mod_PBL_HUD->dpadAlpha;
                Mod_PBL_HUD->dpadAnimator.frameID = 9;
                RSDK.DrawSprite(&Mod_PBL_HUD->dpadAnimator, &Mod_PBL_HUD->dpadPos, true);
            }

            if (player->right) {
                self->alpha                            = opacity;
                Mod_PBL_HUD->dpadTouchAnimator.frameID = 7;
                RSDK.DrawSprite(&Mod_PBL_HUD->dpadTouchAnimator, &Mod_PBL_HUD->dpadPos, true);
            }
            else {
                self->alpha                       = Mod_PBL_HUD->dpadAlpha;
                Mod_PBL_HUD->dpadAnimator.frameID = 7;
                RSDK.DrawSprite(&Mod_PBL_HUD->dpadAnimator, &Mod_PBL_HUD->dpadPos, true);
            }

            if (player->up) {
                self->alpha                            = opacity;
                Mod_PBL_HUD->dpadTouchAnimator.frameID = 8;
                RSDK.DrawSprite(&Mod_PBL_HUD->dpadTouchAnimator, &Mod_PBL_HUD->dpadPos, true);

                if (player->left) {
                    Mod_PBL_HUD->dpadTouchAnimator.frameID = 12;
                    RSDK.DrawSprite(&Mod_PBL_HUD->dpadTouchAnimator, &Mod_PBL_HUD->dpadPos, true);
                }
                else if (player->right) {
                    Mod_PBL_HUD->dpadTouchAnimator.frameID = 13;
                    RSDK.DrawSprite(&Mod_PBL_HUD->dpadTouchAnimator, &Mod_PBL_HUD->dpadPos, true);
                }
            }
            else {
                self->alpha                       = Mod_PBL_HUD->dpadAlpha;
                Mod_PBL_HUD->dpadAnimator.frameID = 8;
                RSDK.DrawSprite(&Mod_PBL_HUD->dpadAnimator, &Mod_PBL_HUD->dpadPos, true);
            }

            if (!player->up && !player->down && !player->left && !player->right) {
                self->alpha                       = Mod_PBL_HUD->dpadAlpha;
                Mod_PBL_HUD->dpadAnimator.frameID = 11;
                RSDK.DrawSprite(&Mod_PBL_HUD->dpadAnimator, &Mod_PBL_HUD->dpadPos, true);
            }

            if (player->jumpHold) {
                self->alpha                            = opacity;
                Mod_PBL_HUD->dpadTouchAnimator.frameID = 1;
                RSDK.DrawSprite(&Mod_PBL_HUD->dpadTouchAnimator, &Mod_PBL_HUD->actionPos, true);
            }
            else {
                self->alpha                       = Mod_PBL_HUD->dpadAlpha;
                Mod_PBL_HUD->dpadAnimator.frameID = 1;
                RSDK.DrawSprite(&Mod_PBL_HUD->dpadAnimator, &Mod_PBL_HUD->actionPos, true);
            }
        }
        else {
            Mod_PBL_HUD->dpadAlpha  = 0;
            Mod_PBL_HUD->pauseAlpha = 0;
        }

        self->alpha                            = Mod_PBL_HUD->pauseAlpha;
        Mod_PBL_HUD->dpadTouchAnimator.frameID = 5;
        RSDK.DrawSprite(&Mod_PBL_HUD->dpadTouchAnimator, &Mod_PBL_HUD->pausePos, true);
    }
    else {
        if (Mod_PBL_HUD->dpadAlpha > 0) {
            Mod_PBL_HUD->dpadAlpha -= 4;
            Mod_PBL_HUD->pauseAlpha -= 8;
        }

        self->alpha = Mod_PBL_HUD->dpadAlpha;
        if (self->alpha > 0) {
            Mod_PBL_HUD->dpadAnimator.frameID = 0;
            RSDK.DrawSprite(&Mod_PBL_HUD->dpadAnimator, &Mod_PBL_HUD->dpadPos, true);

            Mod_PBL_HUD->dpadAnimator.frameID = 1;
            RSDK.DrawSprite(&Mod_PBL_HUD->dpadAnimator, &Mod_PBL_HUD->dpadPos, true);
        }

        if (Mod_PBL_HUD->pauseAlpha < 0)
            self->alpha = 0;
        else
            self->alpha = Mod_PBL_HUD->pauseAlpha;

        Mod_PBL_HUD->dpadTouchAnimator.frameID = 5;
        RSDK.DrawSprite(&Mod_PBL_HUD->dpadTouchAnimator, &Mod_PBL_HUD->pausePos, true);
    }

    self->alpha     = alphaStore;
    self->inkEffect = inkStore;
    self->drawFX    = fxStore;
    self->scale     = scaleStore;
}

void PBL_HUD_Draw(void)
{
    RSDK_THIS(PBL_HUD);

    Mod.Super(PBL_HUD->classID, SUPER_DRAW, NULL);

    PBL_HUD_DrawTouchControls();
}

void PBL_HUD_StageLoad(void)
{
    Mod.Super(PBL_HUD->classID, SUPER_STAGELOAD, NULL);

    Mod_PBL_HUD->dpadFrames = RSDK.LoadSpriteAnimation("Global/TouchControls.bin", SCOPE_STAGE);
    Mod_PBL_HUD->dpadAlpha  = 0;
    Mod_PBL_HUD->pauseAlpha = 0;

    RSDK.SetSpriteAnimation(Mod_PBL_HUD->dpadFrames, 0, &Mod_PBL_HUD->dpadAnimator, true, 0);
    RSDK.SetSpriteAnimation(Mod_PBL_HUD->dpadFrames, 1, &Mod_PBL_HUD->dpadTouchAnimator, true, 0);
}
#endif
