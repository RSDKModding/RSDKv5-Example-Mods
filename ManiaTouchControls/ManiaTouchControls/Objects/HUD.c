#include "HUD.h"
#include "Player.h"
#include "../ModConfig.h"

ObjectHUD *HUD;
ModObjectHUD *Mod_HUD;

void (*HUD_DrawNumbersBase16)(Vector2 *drawPos, int32 value) = NULL;

void HUD_DrawTouchControls(void)
{
    RSDK_THIS(HUD);

    int32 playerID       = SceneInfo->currentScreenID;
    EntityPlayer *player = RSDK_GET_ENTITY(playerID, Player);

    int32 alphaStore   = self->alpha;
    int32 inkStore     = self->inkEffect;
    int32 fxStore      = self->drawFX;
    Vector2 scaleStore = self->scale;

    Mod_HUD->dpadPos.x = TO_FIXED(config.moveDPadPos.x);
    Mod_HUD->dpadPos.y = TO_FIXED(config.moveDPadPos.y);

    Mod_HUD->actionPos.x = TO_FIXED(ScreenInfo[SceneInfo->currentScreenID].size.x + config.jumpDPadPos.x);
    Mod_HUD->actionPos.y = TO_FIXED(config.jumpDPadPos.y);

    Mod_HUD->superPos.x = Mod_HUD->actionPos.x - TO_FIXED(64);
    Mod_HUD->superPos.y = Mod_HUD->actionPos.y;

    Mod_HUD->swapPos.x = Mod_HUD->actionPos.x;
    Mod_HUD->swapPos.y = Mod_HUD->actionPos.y - TO_FIXED(64);

#if MANIA_USE_PLUS
    if (globals->gameMode == MODE_ENCORE) 
        Mod_HUD->pausePos.x = TO_FIXED(ScreenInfo[SceneInfo->currentScreenID].size.x - 100);
    else 
#endif
        Mod_HUD->pausePos.x = TO_FIXED(ScreenInfo[SceneInfo->currentScreenID].size.x - 76);
    Mod_HUD->pausePos.y = TO_FIXED(16);

    self->inkEffect = INK_ALPHA;
    self->drawFX    = FX_SCALE;

    int32 opacity = (int32)(0x100 * config.vDPadOpacity);
    self->scale.x = (int32)(0x200 * config.vDPadSize);
    self->scale.y = (int32)(0x200 * config.vDPadSize);

    bool32 canMove = player->stateInput == Player_Input_P1;
    canMove |= player->stateInput == MegaChopper_Input_GrabbedP1;
    canMove |= player->stateInput == Gachapandora_Player_StateInput_P1Grabbed;
#if MANIA_USE_PLUS
    canMove |= player->stateInput == EncoreIntro_PlayerInput_BuddySel;
#endif

    bool32 canJump = player->stateInput == Player_Input_P1;
    canJump |= player->stateInput == MegaChopper_Input_GrabbedP1;
    canJump |= player->stateInput == Gachapandora_Player_StateInput_P1Grabbed;

    bool32 canSuper = canJump && Player_CanTransform(player);

#if MANIA_USE_PLUS
    bool32 canSwap = canJump && globals->gameMode == MODE_ENCORE && !HUD->swapCooldown && Player_CheckValidState(player) && Player_CanSwap(player);
#endif

    bool32 canPause = canMove;

    Vector2 superPos = Mod_HUD->superPos;
#if MANIA_USE_PLUS
    Vector2 swapPos  = Mod_HUD->swapPos;
#endif

    if (canMove) {
        if (Mod_HUD->dpadAlpha[playerID] < opacity) 
            Mod_HUD->dpadAlpha[playerID] += 4;

        // Draw DPad
        self->alpha                   = Mod_HUD->dpadAlpha[playerID];
        Mod_HUD->dpadAnimator.frameID = 10;
        RSDK.DrawSprite(&Mod_HUD->dpadAnimator, &Mod_HUD->dpadPos, true);

        if (player->left) {
            self->alpha                        = opacity;
            Mod_HUD->dpadTouchAnimator.frameID = 6;
            RSDK.DrawSprite(&Mod_HUD->dpadTouchAnimator, &Mod_HUD->dpadPos, true);
        }
        else {
            self->alpha                   = Mod_HUD->dpadAlpha[playerID];
            Mod_HUD->dpadAnimator.frameID = 6;
            RSDK.DrawSprite(&Mod_HUD->dpadAnimator, &Mod_HUD->dpadPos, true);
        }

        if (player->down) {
            self->alpha                        = opacity;
            Mod_HUD->dpadTouchAnimator.frameID = 9;
            RSDK.DrawSprite(&Mod_HUD->dpadTouchAnimator, &Mod_HUD->dpadPos, true);
        }
        else {
            self->alpha                   = Mod_HUD->dpadAlpha[playerID];
            Mod_HUD->dpadAnimator.frameID = 9;
            RSDK.DrawSprite(&Mod_HUD->dpadAnimator, &Mod_HUD->dpadPos, true);
        }

        if (player->right) {
            self->alpha                        = opacity;
            Mod_HUD->dpadTouchAnimator.frameID = 7;
            RSDK.DrawSprite(&Mod_HUD->dpadTouchAnimator, &Mod_HUD->dpadPos, true);
        }
        else {
            self->alpha                   = Mod_HUD->dpadAlpha[playerID];
            Mod_HUD->dpadAnimator.frameID = 7;
            RSDK.DrawSprite(&Mod_HUD->dpadAnimator, &Mod_HUD->dpadPos, true);
        }

        if (player->up) {
            self->alpha                        = opacity;
            Mod_HUD->dpadTouchAnimator.frameID = 8;
            RSDK.DrawSprite(&Mod_HUD->dpadTouchAnimator, &Mod_HUD->dpadPos, true);
        }
        else {
            self->alpha                   = Mod_HUD->dpadAlpha[playerID];
            Mod_HUD->dpadAnimator.frameID = 8;
            RSDK.DrawSprite(&Mod_HUD->dpadAnimator, &Mod_HUD->dpadPos, true);
        }
        if (!player->up && !player->down && !player->left && !player->right) {
            self->alpha                   = Mod_HUD->dpadAlpha[playerID];
            Mod_HUD->dpadAnimator.frameID = 11;
            RSDK.DrawSprite(&Mod_HUD->dpadAnimator, &Mod_HUD->dpadPos, true);
        }
    }
    else {
        if (Mod_HUD->dpadAlpha[playerID] > 0) {
            Mod_HUD->dpadAlpha[playerID] -= 4;
        }

        self->alpha = Mod_HUD->dpadAlpha[playerID];
        if (self->alpha > 0) {
            Mod_HUD->dpadAnimator.frameID = 0;
            RSDK.DrawSprite(&Mod_HUD->dpadAnimator, &Mod_HUD->dpadPos, true);
        }
    }

    if (canJump) {
        if ((SceneInfo->state & 3) == ENGINESTATE_REGULAR) {
            if (Mod_HUD->jumpAlpha[playerID] < opacity)
                Mod_HUD->jumpAlpha[playerID] += 4;

            if (player->jumpHold) {
                self->alpha                        = opacity;
                Mod_HUD->dpadTouchAnimator.frameID = 1;
                RSDK.DrawSprite(&Mod_HUD->dpadTouchAnimator, &Mod_HUD->actionPos, true);
            }
            else {
                self->alpha                   = Mod_HUD->jumpAlpha[playerID];
                Mod_HUD->dpadAnimator.frameID = 1;
                RSDK.DrawSprite(&Mod_HUD->dpadAnimator, &Mod_HUD->actionPos, true);
            }
        }
        else {
            Mod_HUD->jumpAlpha[playerID] = 0;
        }
    }
    else {
        if (Mod_HUD->jumpAlpha[playerID] > 0) 
            Mod_HUD->jumpAlpha[playerID] -= 4;

        self->alpha = Mod_HUD->jumpAlpha[playerID];
        if (self->alpha > 0) {
            Mod_HUD->dpadAnimator.frameID = 1;
            RSDK.DrawSprite(&Mod_HUD->dpadAnimator, &Mod_HUD->actionPos, true);
        }
    }

    if (canSuper) {
        if ((SceneInfo->state & 3) == ENGINESTATE_REGULAR) {
            if (Mod_HUD->superAlpha[playerID] < opacity)
                Mod_HUD->superAlpha[playerID] += 4;

            if (!player->onGround && ControllerInfo[player->controllerID].keyY.down) {
                self->alpha                        = opacity;
                Mod_HUD->dpadTouchAnimator.frameID = 3;
                RSDK.DrawSprite(&Mod_HUD->dpadTouchAnimator, &superPos, true);
            }
            else {
                self->alpha                   = Mod_HUD->superAlpha[playerID];
                Mod_HUD->dpadAnimator.frameID = 3;
                RSDK.DrawSprite(&Mod_HUD->dpadAnimator, &superPos, true);
            }
        }
        else {
            Mod_HUD->superAlpha[playerID] = 0;
        }
    }
    else {
        if (Mod_HUD->superAlpha[playerID] > 0)
            Mod_HUD->superAlpha[playerID] -= 4;

        self->alpha = Mod_HUD->superAlpha[playerID];
        if (self->alpha > 0) {
            Mod_HUD->dpadAnimator.frameID = 3;
            RSDK.DrawSprite(&Mod_HUD->dpadAnimator, &superPos, true);
        }
    }

#if MANIA_USE_PLUS
    if (canSwap) {
        if ((SceneInfo->state & 3) == ENGINESTATE_REGULAR) {
            if (Mod_HUD->swapAlpha[playerID] < opacity)
                Mod_HUD->swapAlpha[playerID] += 4;

            if (player->onGround && ControllerInfo[player->controllerID].keyY.down) {
                self->alpha                        = opacity;
                Mod_HUD->dpadTouchAnimator.frameID = 4;
                RSDK.DrawSprite(&Mod_HUD->dpadTouchAnimator, &swapPos, true);
            }
            else {
                self->alpha                   = Mod_HUD->swapAlpha[playerID];
                Mod_HUD->dpadAnimator.frameID = 4;
                RSDK.DrawSprite(&Mod_HUD->dpadAnimator, &swapPos, true);
            }
        }
        else {
            Mod_HUD->swapAlpha[playerID] = 0;
        }
    }
    else {
        if (Mod_HUD->swapAlpha[playerID] > 0)
            Mod_HUD->swapAlpha[playerID] -= 4;

        self->alpha = Mod_HUD->swapAlpha[playerID];
        if (self->alpha > 0) {
            Mod_HUD->dpadAnimator.frameID = 4;
            RSDK.DrawSprite(&Mod_HUD->dpadAnimator, &swapPos, true);
        }
    }
#endif

    if (canPause) {
        if ((SceneInfo->state & 3) == ENGINESTATE_REGULAR) {
            if (Mod_HUD->pauseAlpha[playerID] < opacity)
                Mod_HUD->pauseAlpha[playerID] += 8;

            self->alpha                        = Mod_HUD->pauseAlpha[playerID];
            Mod_HUD->dpadTouchAnimator.frameID = 5;
            RSDK.DrawSprite(&Mod_HUD->dpadTouchAnimator, &Mod_HUD->pausePos, true);
        }
        else {
            Mod_HUD->pauseAlpha[playerID] = 0;
        }
    }
    else {
        if (Mod_HUD->pauseAlpha[playerID] > 0)
            Mod_HUD->pauseAlpha[playerID] -= 8;

        self->alpha = Mod_HUD->pauseAlpha[playerID];
        if (self->alpha > 0) {
            Mod_HUD->dpadTouchAnimator.frameID = 5;
            RSDK.DrawSprite(&Mod_HUD->dpadTouchAnimator, &Mod_HUD->pausePos, true);
        }
    }

    self->alpha     = alphaStore;
    self->inkEffect = inkStore;
    self->drawFX    = fxStore;
    self->scale     = scaleStore;
}

void HUD_DrawMobileHUD(void) {
    RSDK_THIS(HUD);
    
    EntityPlayer *player = RSDK_GET_ENTITY(SceneInfo->currentScreenID, Player);
    Vector2 drawPos;

    Object *debugModeSVars = Mod.FindObject("DebugMode");
    if (debugModeSVars && RSDK_GET_ENTITY(SLOT_PLAYER1, Player)->classID == debugModeSVars->classID) {
        if (player->camera) {
            // Draw Camera YPos
            drawPos.x = TO_FIXED(ScreenInfo[player->camera->screenID].size.x - 16);
            drawPos.y = TO_FIXED(48);
            HUD_DrawNumbersBase16(&drawPos, ScreenInfo[player->camera->screenID].position.y);

            // Draw Camera XPos
            drawPos.x -= TO_FIXED(9);
            HUD_DrawNumbersBase16(&drawPos, ScreenInfo[player->camera->screenID].position.x);

            // Draw Player YPos
            drawPos.x = TO_FIXED(ScreenInfo[player->camera->screenID].size.x - 16);
            drawPos.y += TO_FIXED(16);
            HUD_DrawNumbersBase16(&drawPos, FROM_FIXED(player->position.y));

            // Draw Player XPos
            drawPos.x -= TO_FIXED(9);
            HUD_DrawNumbersBase16(&drawPos, FROM_FIXED(player->position.x));
        }
    }
}

void HUD_Draw(void)
{
    RSDK_THIS(HUD);

    EntityPlayer *player = RSDK_GET_ENTITY(SceneInfo->currentScreenID, Player);

    int32 playerClassID = player->classID;
    void *playerCamera  = player->camera;

    // make the game think we should have debug mode enabled
    // however NULL the camera to draw nothing
    Object *debugModeSVars = Mod.FindObject("DebugMode");
    if (debugModeSVars)
        player->classID = debugModeSVars->classID;
    else
        player->classID = TYPE_BLANK;
    player->camera      = NULL;

    Vector2 lifePos = self->lifePos;
#if MANIA_USE_PLUS
    if (globals->gameMode == MODE_COMPETITION) {
        lifePos         = self->vsLifePos[SceneInfo->currentScreenID];

        self->vsLifePos[SceneInfo->currentScreenID].x = TO_FIXED(ScreenInfo[SceneInfo->currentScreenID].size.x - 48) - lifePos.x;
        self->vsLifePos[SceneInfo->currentScreenID].y = TO_FIXED(25);
    }
    else if (globals->gameMode == MODE_ENCORE) {
        self->lifePos.x = TO_FIXED(ScreenInfo[SceneInfo->currentScreenID].size.x - 72) - lifePos.x;
        self->lifePos.y = TO_FIXED(25);
    }
    else {
#endif
        self->lifePos.x = TO_FIXED(ScreenInfo[SceneInfo->currentScreenID].size.x - 48) - lifePos.x;
        self->lifePos.y = TO_FIXED(25);
#if MANIA_USE_PLUS
    }
#endif

    // Draw HUD stuff
    Mod.Super(HUD->classID, SUPER_DRAW, NULL);

    // Draw Mobile HUD bits
    HUD_DrawMobileHUD();

    player->classID = playerClassID;
    player->camera  = playerCamera;

#if MANIA_USE_PLUS
    if (globals->gameMode == MODE_COMPETITION) 
        self->vsLifePos[SceneInfo->currentScreenID] = lifePos;
    else
#endif
        self->lifePos = lifePos;

    HUD_DrawTouchControls();
}

void HUD_StageLoad(void)
{
    Mod.Super(HUD->classID, SUPER_STAGELOAD, NULL);

    Mod_HUD->dpadFrames = RSDK.LoadSpriteAnimation("Global/TouchControls.bin", SCOPE_STAGE);

    RSDK.SetSpriteAnimation(Mod_HUD->dpadFrames, 0, &Mod_HUD->dpadAnimator, true, 0);
    RSDK.SetSpriteAnimation(Mod_HUD->dpadFrames, 1, &Mod_HUD->dpadTouchAnimator, true, 0);
}
